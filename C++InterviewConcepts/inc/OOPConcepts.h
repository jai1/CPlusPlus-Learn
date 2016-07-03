/*
 * OOPConcepts.h
 *
 *  Created on: Oct 5, 2015
 *      Author: Jai
 */
#include <iostream>
using namespace std;
#ifndef OOPCONCEPTS_H_
#define OOPCONCEPTS_H_

class OOPConcepts {
public:
	OOPConcepts();
	virtual ~OOPConcepts();

	void run();

private:
	int OOPConcepts::divide (int a, int b);
	float OOPConcepts::divide (float a, float b);
// need -fpermissive since float and int come under the same hierarchry
	void OOPConcepts::operatorOverloading();
	void OOPConcepts::virtualDestructors();
	void OOPConcepts::functionOverloading();
};

#endif /* OOPCONCEPTS_H_ */
