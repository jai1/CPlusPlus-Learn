// forward example
#include <utility>      // std::forward
#include <iostream>     // std::cout

using namespace std;



// function with lvalue and rvalue reference overloads:
void overloaded (const int& x) {std::cout << "[lvalue]";}
void overloaded (int&& x) {std::cout << "[rvalue]";}

// function template taking rvalue reference to deduced type:
template <class T> void fn (T&& x) {
  overloaded (x);                   // always an lvalue
  overloaded (std::forward<T>(x));  // rvalue if argument is rvalue
}

int main () {

    auto multiply = [] (const int& x, const int& y) { return x*y; };

    // rvalue vs lvalue

    /**
     * Example of lvalues - any thing that has an address or is not a rvalue
     * x
     * *x
     * x[10]
   **/

   /**
     * Examples or rvalues
     * 2       - constants (address is not in memory it is in executable - code section)
     * x + y   - temporary objects
     * func()  - remporary objects
   **/

    // Pre C++11
    int a = 10;
    int &x = a; // taking reference
    // int &y = 10; // fails since 10 is not a lvalue
    const int &y = 10; // hence comes a concept of const reference where you can take a read only reference of the rvalue
    const int &z = multiply(10, 5);  // same as above

    // C++11
    int &&b = 10; // rvalue reference - internally a temp space is allocated on stack with val = 10 
    b = b + 1; // val in the temp space is modified
    cout << "b = " << b << endl;

    // like const lvalue reference, rvalue reference prolongs the death of the temp object till the reference is alive
    // if the rvalue of a variable is taken (may be using move) and the variable dies, just like lvalue - rvalue will become a dangling pointer which may crash the program so make sure that you do a std::move only on function parameters and not on return types and try not to return rvalue references. 

    // std::move casts into rvalue and is used to call the rvalue overloaded version of the function
    cout<<endl<<"version called is ";
    overloaded(b); // calls the lvalue version of the function since I may still want to use b after calling the function

    cout<<endl<<"version called is ";
    overloaded(std::move(b)); // calls rvalue version of the function, since by calling move I guarantee that i don't have any use of b

    cout<<endl;

    // std::forward - forward is similar to move but it only casts to rvalue if the variable is a rvalue, else it casts to lvalue
    // like move make sure that u don't use the variable after calling a function with forwarded rvalue
    std::cout << "calling fn with lvalue: ";
    fn (a);
    std::cout << '\n';

    std::cout << "calling fn with rvalue: ";
    fn (0);
    std::cout << '\n';

/*
    NOTE:-
    In copy constructors and assignment operators with move semantics, make sure that the original object pointers are poining to NULL,
    since the original object (temp object) will still be destructed.

    move sematics doesn't mean that you are actually performing a move, it only means that that you are calling the revalue reference overload
    of the function and relying on the function to perform the move.
*/

    return 0;
}
