/*
 * Car.h
 *
 *  Created on: Oct 5, 2015
 *      Author: Jai
 */
#include <iostream>
using namespace std;
#include "Vehicle.h"
#ifndef CAR_H_
#define CAR_H_

class Car: public Vehicle {
public:
	Car(int price);
	~Car();
};

#endif /* CAR_H_ */
