#include <iostream>
#include <deque>
#include <thread>
#include <future>
#include <chrono>
using namespace std;

// use packaged task to run a thread somewhere else
int factorial(int n) {
    return n <= 1 ? 1 : n * factorial(n-1);
}

deque<packaged_task<int ()> > tasks;
mutex mu;
condition_variable cond;

void thread_1() {
    packaged_task<int ()> t;
    {
        std::unique_lock<mutex> lock(mu);

        // wait for a task to be pushed before popin
        // before reacquiring the lock we check the predicate 
        cond.wait(lock, []() { return !tasks.empty();});    

        t = std::move(tasks.front());
        tasks.pop_front();
    }
    t();
}

int main() {    
    thread t1(thread_1);
    t1.detach();
    // packaged task takes only a function with no arguments
    // it is not a variadic template
    // hence we use bind
    packaged_task<int ()> t(bind(factorial, 6));
    future<int> fu = t.get_future();

    {
        std::lock_guard<mutex> lock(mu);
        tasks.push_back(std::move(t));
        cond.notify_one();
    }
    
    std::future_status status = fu.wait_for(chrono::milliseconds(4000)); 
    // wait for the function to return a value

    if (status == std::future_status::ready)
        cout<<fu.get();
    return 0;
}
