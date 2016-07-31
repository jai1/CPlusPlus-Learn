#include <iostream>    // cout
#include <typeinfo>    // for 'typeid'

class Person {
public:
   virtual ~Person() {}
};

class Employee : public Person {
};


class A {
public:
    // Since RTTI is included in the virtual method table there should be at least one virtual function.
    virtual ~A() { };
    void methodSpecificToA() { std::cout << "Method specific for A was invoked" << std::endl; };
};
 
class B : public A {
public:
    void methodSpecificToB() { std::cout << "Method specific for B was invoked" << std::endl; };
    virtual ~B() { };
};
 
void my_function(A& my_a)
{
    try {
        B& my_b = dynamic_cast<B&>(my_a); // cast will be successful only for B type objects.
        my_b.methodSpecificToB();
    }
    catch (const std::bad_cast& e) {
        std::cerr << "  Exception " << e.what() << " thrown." << std::endl;
        std::cerr << "  Object is not of type B" << std::endl;
    }
}



int main() 
{
   Person person;
   Employee employee;
   Person* ptr = &employee;
   Person& ref = employee;
   // The string returned by typeid::name is implementation-defined
   std::cout << typeid(person).name() << std::endl;   // Person (statically known at compile-time)
   std::cout << typeid(employee).name() << std::endl; // Employee (statically known at compile-time)
   std::cout << typeid(ptr).name() << std::endl;      // Person* (statically known at compile-time)
   std::cout << typeid(*ptr).name() << std::endl;     // Employee (looked up dynamically at run-time
                                                      //           because it is the dereference of a
                                                      //           pointer to a polymorphic class)
   std::cout << typeid(ref).name() << std::endl;      // Employee (references can also be polymorphic)

   Person* p = nullptr;
   try {
      typeid(*p); // not undefined behavior; throws std::bad_typeid
   }
   catch (...) {
   }

   Person& pRef = *p; // Undefined behavior: dereferencing null
   typeid(pRef);      // does not meet requirements to throw std::bad_typeid
                      // because the expression for typeid is not the result
                      // of applying the unary * operator


    A *arrayOfA[3];          // Array of pointers to base class (A)
    arrayOfA[0] = new B();   // Pointer to B object
    arrayOfA[1] = new B();   // Pointer to B object
    arrayOfA[2] = new A();   // Pointer to A object
    for (int i = 0; i < 3; i++) {
        my_function(*arrayOfA[i]);
        delete arrayOfA[i];  // delete object to prevent memory leak
    }

}
