#include<iostream>

using namespace std;

class A {
    public:
    A() {}
    A(int a) {}
    void fn() {}
};

int fn(A obj) {


}

class B {
    public:
    B(A obj) {}
};


/*
    Expressions that can be evaluated as function definitions will
    be considered as function definitions.
*/
int main() {
    A obj1(); 
    // will compile but here we are not creating an object obj1
    // we are creating a function obj1 which returns A and takes no arguments
    // usually a warning is generated for this.
    A obj2(1);
    // obj1.fn(); // Due to the above mentioned reason, this statement doesn't compile
    obj2.fn();
    
    // OK
    int a = fn(obj2);
    // OK
    a = fn(A());
    // OK
    a = fn(A(2));

    // All 3 OK
    B obj3(A());
    B obj4(A(1));
    B obj5(obj2);
}
