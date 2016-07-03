/*
 * Car.cpp
 *
 *  Created on: Oct 5, 2015
 *      Author: Jai
 */

#include "Car.h"

Car::Car(int price) : Vehicle(price)
// Need this implicit call to call parameterized Vehicle Constructor
// else default constructor Vehicle() is called.
{
	// TODO Auto-generated constructor stub
	cout<<"In Cars Constructor - The price is "<<price<<endl;

}

Car::~Car() {
	cout<<"Tn Cars Destructor"<<endl;
	// TODO Auto-generated destructor stub
}

