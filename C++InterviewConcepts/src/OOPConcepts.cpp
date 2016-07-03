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
	Vehicle *v = new Car(10000);
	delete v;
}
