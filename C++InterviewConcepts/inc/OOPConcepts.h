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
	int divide (int a, int b);
	float divide (float a, float b);
// need -fpermissive since float and int come under the same hierarchry
	void operatorOverloading();
	void virtualDestructors();
	void functionOverloading();
};

#endif /* OOPCONCEPTS_H_ */
