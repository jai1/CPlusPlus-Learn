#include<iostream>
#include<future>
#include<map>
#include<ctime>
#include<chrono>
#include<mutex>
#include<thread>
#include<string>
using namespace std;

/*
    Future is used to get result from child thread
    Promise is used to pass calue from one thread to other - promise needs to be kept else the code could hang up.
    If for some reason you can't keep the promise you can use set_exception and pass a user defined exception which can be caught by the thread waiting on get() of the promise's future.

    Promise and Future can only be moved, not copied.
    shared_future is used to pass future to mutliple threads.

    Promise get_future can be called only once.
    Future get() can be called multiple times but the computation is done only once and cached. All get() calls are served from this cache (as value) -- copy.    
    3 ways of getting a future:-
    a. promise.get_future()
    b. async()
    c. packaged_task::get_future() // seen in next chapter

*/


std::mutex mtx;

std::string now( const char* format = "%c" )
{
    std::time_t t = std::time(0) ;
    char cstr[128] ;
    std::strftime( cstr, sizeof(cstr), format, std::localtime(&t) ) ;
    return cstr ;
}

long factorial(int num) {
    if(num <= 1) {
        // use locker instead of lock as variable name, since lock is also a function name. It's not giving an error now since you have not included the locks header.
        lock_guard<std::mutex> lock(mtx);
        cout<<"Thread id = " << std::this_thread::get_id() << endl;
        cout<<"time = " << now() << endl;
        return 1;
    }
    else
        return num * factorial(num - 1);
}

// Can only take futre by reference
long ffactorial(future<int>& f) {
    // do some initialization
    return factorial(f.get());
}

long overloaded(int /* ignore */) {}

long overloaded(string /* ignore */) {}

int main() {
    
    map<int, future<long> > m;
    for (int i = 0; i<10; i++) 
        m[i] = std::async(std::launch::async, factorial, i); // async returns a future

    for (int i = 10; i<20; i++)
        m[i] = std::async(std::launch::deferred, factorial, i);
    
    /*
      std::async(std::launch::async, factorial, i); -- create a new thread immediately
      std::async(std::launch::deferred, factorial, i); -- wait for get() to be called, usually runs on the get() thread
      std::async(std::launch::async | std::launch::deferred, factorial, i); -- let system determine 
    
    Note: async can't take an overloaded class function, since at which version of the function pointer to use can only be determined after looking at the arguments. Since async uses variadic template it can't determine which function to use.
    Variadic Template - Template with variable number of arguments
    
    To overcome this issue use:-
        async(std::launch::async, [capture]();
    */
    
    for (int i = 10; i<20; i++)
        m[i] = std::async(std::launch::deferred, factorial, i); 

    // do something else 

    for (int i; i<20; i++) {
        long result = m[i].get();
        lock_guard<std::mutex> lock(mtx); // lock only after get, else there will be deadlock with factorial function
        cout<<"Factorial of "<< i << " = " << result << endl; // wait for task to complete 
        cout<<"time = " << now() << endl;
    }

    
    promise<int> p;
    future<int> f = p.get_future();

    future<long> result = async(ffactorial, std::ref(f));
   
    int num; 
    cout<<"Please enter a number:";
    cin>>num;
    
    p.set_value(num);

    int r = result.get();   
    int s = result.get(); 
    lock_guard<std::mutex> lock(mtx);
    cout << "Factorial of entered number[" << num <<  "] is " << r;
    cout << "Factorial of entered number[" << num <<  "] is " << s;

    int temp = 50;
    // result = async(overloaded, temp); // doesn't work
    /* 
    async can't take an overloaded class function, since at which version of the function pointer to use can only be determined after looking at the arguments. Since async uses variadic template it can't determine which function to use.
    Variadic Template - Template with variable number of arguments
    
    In case of non variadic template, we could take the params first and then function name and done with something lie this:-  

    template<typename A1, typename A2, typename R>
    auto doit( A1 a1, A2 a2, R (*f) (A1,A2)) -> R {
        return f(a1, a2);
    }
    

    To overcome this issue use lambda
    [ capture-list ] ( params ) -> ret { body }
    */
    
    
    result = async([temp]() -> long {return overloaded(temp);});   
 
    return 0;
}
