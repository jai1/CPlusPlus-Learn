/*
 * Vehicle.h
 *
 *  Created on: Oct 5, 2015
 *      Author: Jai
 */
#include <iostream>
using namespace std;

#ifndef VEHICLE_H_
#define VEHICLE_H_

class Vehicle {
public:
	Vehicle(int p);
	Vehicle();
	virtual ~Vehicle();
	// Need to make the destructor virtual else if the
	// base class is deleted the destructor of the
	// derived class is never called.

	// Before Virtual and implicit call to Vehicle(int):-
	//	- Vehicle Constructor is called
	//	- In Cars Constructor - The price is 10000
	//	- In Vehicles Destructor

	// After Virtual and implicit call to Vehicle(int):-
	//	- Vehicle price is 10000
	//	- In Cars Constructor - The price is 10000
	//	- Tn Cars Destructor
	//	- In Vehicles Destructor


};

#endif /* VEHICLE_H_ */
