/*
 * Basics.h
 *
 *  Created on: Oct 5, 2015
 *      Author: Jai
 */
#include <iostream>
using namespace std;

#ifndef BASICS_H_
#define BASICS_H_

class Basics {
public:
	Basics();
	virtual ~Basics();
	void run();
	static void staticFunction();

private:
	void functionWithStaticVariable();

	void info();

	void learnEnums();
};

#endif /* BASICS_H_ */
