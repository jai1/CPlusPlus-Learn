#include <iostream>
#include <thread>
#include <string>
using namespace std;

    //For locks always use RAII else in case of exceptions you may end up never releasing the lock

    // atomic vs lock (full barrier) - https://channel9.msdn.com/Shows/Going+Deep/Cpp-and-Beyond-2012-Herb-Sutter-atomic-Weapons-1-of-2
    // https://www.youtube.com/watch?v=c1gO9aB9nbs

    // Types of locks:-
    // scoped_lock
    // lock_guard - pure RAII + can defer lock - can't be moved
    // unique_lock - RAII + can defer lock + lock, unlock function + can be moved - little more heavy weighted than a lock_guard
    // shared_lock - slow
    // reenterant_lock
    

    // Problems with locks - 
    // Data Races - banking example
    // Dead lock - A wants to re acquire the lock which A already acquired
    //           + soln: use reenterant_lock 
    //           + Avoid locking a mutex and calling other functions which 
    //             may ask for the lock again.
    //           + avoid completing promise or callbacks under a lock
    //           - A wants to acquire the lock which B has
    //             B wants to acquire the lock which A has 
    //           + Always acquire the lock in the same order 


    // Sometime you want to initialize a resource only once - like opening a file
    // but using threads or atomics you still need to acquire a lock and always check already opened flag - since c++ doesn't support double checked locking idiom - http://preshing.com/20130930/double-checked-locking-is-fixed-in-cpp11/
    // instead use std::call_once  

struct bank_account {
    explicit bank_account(int balance) : balance(balance) {}
    int balance;
    std::mutex m;
};
 
void transfer(bank_account &from, bank_account &to, int amount)
{
    // lock both mutexes without deadlock - by ensuring that from.m is locked before to.m
    std::lock(from.m, to.m);
    
    // make sure both already-locked mutexes are unlocked at the end of scope
    // RAII
    std::lock_guard<std::mutex> lock1(from.m, std::adopt_lock);
    std::lock_guard<std::mutex> lock2(to.m, std::adopt_lock);
 
// equivalent approach:
//    std::unique_lock<std::mutex> lock1(from.m, std::defer_lock);
//    std::unique_lock<std::mutex> lock2(to.m, std::defer_lock);
//    std::lock(lock1, lock2);
    /*
    defer_lock_t    do not acquire ownership of the mutex
    try_to_lock_t   try to acquire ownership of the mutex without blocking
    adopt_lock_t    assume the calling thread already has ownership of the mutex
    defer_locks can be used for during lazy initialization or initialization on first use idiom - eg lock only if there is space available in blocking queue
    */

    from.balance -= amount;
    to.balance += amount;
}
 
int main()
{
    bank_account my_account(100);
    bank_account your_account(50);
 
    std::thread t1(transfer, std::ref(my_account), std::ref(your_account), 10);
    std::thread t2(transfer, std::ref(your_account), std::ref(my_account), 5);
 
    t1.join();
    t2.join();
}
