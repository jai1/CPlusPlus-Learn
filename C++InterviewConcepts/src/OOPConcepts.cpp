/*
 * OOPConcepts.cpp
 *
 *  Created on: Oct 5, 2015
 *      Author: Jai
 */

#include "Vehicle.h"
#include "Car.h"
#include "OOPConcepts.h"
#include "Complex.h"
#include <stdexcept>
OOPConcepts::OOPConcepts() {
	// TODO Auto-generated constructor stub

}

OOPConcepts::~OOPConcepts() {
	// TODO Auto-generated destructor stub
}


void OOPConcepts::operatorOverloading() {
	Complex a(2,3);
	Complex b(1,2);
	cout<<a+b<<endl;
}

void OOPConcepts::run() {
	// Operator overloading
	operatorOverloading();

	// Virtual Destructors
	virtualDestructors();

	// overloading
	functionOverloading();

	// Inheritance guidelines:-
	// a. Multiple inheritance - https://www.youtube.com/watch?v=7APovvvftQs&index=5&list=WL
	//    In short use java approach - inherit only one class and multiple interfaces (Pure abstract classes)
	//    Keep interfaces as short and concise as possible s
	// b. Don't use inheritance for code re use, use composition instead, i.e if two classes have similar functions
	//    don't inherit one from other, just transfer the functions to a separate helper class and give both the classes
	//    an object of the helper class.
	// c. Minimize base class implementation
	// d. Minimize level of hierarchies
	// e. Inheritance breaks encapsulation. (since a child can access parents protected members)

	// Koenig Lookup - Argument Dependent Lookup for namespaces only - not applicable to classes
	//

}

int OOPConcepts::divide (int a, int b) {
	if(b)
		return a/b;
	else
		throw runtime_error("Cannot Divide by 0");
}

float OOPConcepts::divide (float a, float b) {
	if(b)
		return a/b;
	else
		throw runtime_error("Cannot Divide by 0");
}

void OOPConcepts::functionOverloading() {
	cout<<"The outputs are: ";
	cout<<divide(float(2.0),float(0.5))<<" "<<divide(4,2)<<" ";
	int quotient =  divide(float(22.0),float(7.0));
	cout<<quotient<<endl;

	// Since by default 2.0 is double explicit conversion to float is required
	// int convert the floating point number to Integer (floor)
}

std::ostream& operator<<(std::ostream& a, Complex c) {
	a<<"[ Real= "<<c.getReal()<<" , "<<"Img= "<<c.getImg()<<" ]";
	return a;
}

void OOPConcepts::virtualDestructors() {
	// Virtualisation as a concept works only on public inheritance
	// class YellowDog : Dog (w/o public) - means private inheritance
	// You can't do Dog *d = new YellowDog(); if it is a private inheritance

//	/* Return type rules for overriding
//	Overriding essentially means that either the Base class method or the Derived class method will be called at run-time depending on the actual object pointed by the pointer.
//	It implies that:
//	i.e: Every place where the Base class method can be called can be replaced by call to Derived class method without any change to calling code.
//
//	In order to achieve this the only possible way is to restrict the return types of the overriding virtual methods to return the same type as the Base class or a type derived from that(co-variant return types) and the Standard enforces this condition.
//	 */

	Vehicle *v = new Car(10000);
	// If the vehicle didn't have a virtual destructor then
	// the cars destructor will not be called
	delete v;

	// Virtual is inherited hence if we created a class CustomCars
	// which inherits Cars did a (new CustomCars), base class pointer
	// would still call derived class functions eventhough Cars doesn't
	// define functions as virtual (since Vehicle - Car's base) has defined them virtual.
	// This works for all virtual functions (which includes destructors)

	// Deciding if I need a virtual destructor when creating base class?
	// A. If any of my functions are virtual, you need to define the destructor as virtual

	// C++11
	// shared_ptr can call the derived class functions and destructors w/o using virtual
	// This is only true for shared_ptr, doesn't apply to unique or scoped ptr
	// STL don't have virtual function hence if you decide to derive an STL class, use
	// a shared_ptr.
}
