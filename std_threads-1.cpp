#include <iostream>
#include <thread>
#include <string>
using namespace std;

/*
    Thread 
    ==pros==
    - light weight
    - low overhead
    - communication through shared memory is faster than IPC
    ==cons==
    - Can't be scaled accross distributed systems 
        -- some people use IPC for thread communication to make it scalable
    - Difficult to implement
*/


void function_1() {
    cout<<"Hi"<<endl;
}

class Func {
    public:
    void operator()(string name) {
        cout<<"Hello, my name is "<<name<<endl;
    }

};

class JoiningThread {
    thread t;
    public:

    JoiningThread(thread&& t) {
        this->t.swap(t);
    }
    JoiningThread (const JoiningThread& /* ignore */) = delete;
    // JoiningThread& operator=(const JoiningThread& /* ignore */) = delete;
    ~JoiningThread() {
        join();
    }

    void join() {
        if (t.joinable())
            t.join();
    }
};

class Item {
    int itemNumber = 0;
    int quantity = 0;
    public:
    Item() { }
    Item(int itemNumber, int quantity) : itemNumber(itemNumber), quantity(quantity) {}
    Item(const Item& /* ignore*/) {} // copy constructor does nothing
    void print() {
        cout<<"itemNumber = "<<itemNumber<<endl;
        cout<<"quantity = "<<quantity<<endl;
    }
};


class Order {
    int orderNumber = 0;
    public:
    Order(int orderNumber) : orderNumber(orderNumber) {} 
    Order(const Order& /* ignore*/) {} // copy constructor does nothing

    int print(Item item) {
        cout<<"orderNumber = "<<orderNumber<<endl;
        item.print();
        return 0;
    }

    int print_with_ref(Item& item) {
        cout<<"orderNumber = "<<orderNumber<<endl;
        item.print();
        return 0;
    }

};

void customSleep(long milliseconds) {
    usleep(milliseconds);
    cout<<"finished sleeping for "<<this_thread::get_id()<<endl;
}

int main() {
    thread t1(function_1);
    t1.join(); // join means wait for the thread to complete
    // t1.join(); // exception since join can be called only once

    thread t2(Func(), "jai"); // using functor
    if (t2.joinable()) // to avoid exception
        t2.join();

    Item item(123, 10);
    Order ord(1);

    // using RAII to join the threads
    JoiningThread j1(std::move(thread(&Order::print, &ord, item)));
    // prints ordernumber correctly but item is incorrect since we pass by value and copy constructor is disabled.

    // To prevent timing issue with j2
    j1.join();
    {
        // passing item by reference - use std::ref
        JoiningThread j2(std::move(thread(&Order::print_with_ref, &ord, std::ref(item))));
        // Correctly prints itemNumber and orderNumber
    }
    
    thread t3(customSleep, 1*1000*1000);
    cout<<"started thread = "<<t3.get_id()<<endl;
    // core dump / terminating error since t3 is not complete

    // detach will avoid the errors mentioned above (try commenting the line and see) BUT main never waits for the threads to complete
    // all resources, threads get killed when main exits

    t3.detach(); 
    // t3.detach(); - like join we can dettach only once
   
    // t3.join();
    // detached thread can't be reattached 

    // join and attach errors are run time errors - not compile time 

    // thread can only be moved NOT copied

    // Oversubscription - number of threads > num of CPU * num of threads
    // leads to degradation of performance due to context switching
    cout << "Number of cores = " << thread::hardware_concurrency()<<endl;
}
