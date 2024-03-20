/*
 * cloneDesignPattern.cpp
 *
 *  Created on: Aug 14, 2016
 *      Author: jai1
 */

#include<iostream>
#include<string>
using namespace std;

class Dog {
public:
	virtual void bark() {
		cout<<"Dog has barked"<<endl;
	}

	// Part 2
	virtual Dog* clone() {
		return new Dog(*this);
	}
};

class YellowDog : public Dog {
public:
	string color = "Yellow";
	void bark() {
		cout<<color<<" Dog has barked"<<endl;
	}

	// Part 2
	Dog* clone() {
		return new YellowDog(*this);
	}
};

Dog* copy(Dog *d) {
	Dog* d3 = d;
	return d3;
}

int main() {
	// Part 1 - since d1, d2 and d3
	// all point to same yellowDog hence all 3
	// Statement shows "Yellow Dog has barked"

	Dog *d1 = new YellowDog();
	((YellowDog *)d1)->color = "Yellow";
	d1->bark();
	Dog *d2 = d1;
	d2->bark();

	Dog *d3 = copy(d1);
	d3->bark();

	delete d1;

	// Part 2 - What if we create new objects using default copy constructors

	d1 = new YellowDog();
	((YellowDog *)d1)->color = "Yellow";
	d1->bark();

	// Now d2 prints "Dog has barked"
	// Since the default copy constructor creates a new object Dog (not YellowDog)
	// and just copies members of d1

	d2 = new Dog(*d1);
	d2->bark();

	// Solution use clone function
	d2 = d1->clone();
	d2->bark();

    // Part 3 - Object Slicing
    // Object Slicing - when a derived class object is passed by value to a 
    //                  base class object. The new base class object created
    //                  via the copy constructor or the assignment operator
    //                  will be of type base class and not derived.

    YellowDog a;
    // print "Yellow Dog has barked"
    a.bark();
    
    Dog b = a;
    // prints "Dog has barked" 
    b.bark();

    // Object slicing is a big problem in STL containers of type Base Class Objects.
    
    // To avoid object slicing use STL containers with base class pointers or smart pointers BUT remember to keep the functions virtual for all cases except smart_pointers.

}
