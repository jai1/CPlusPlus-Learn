//============================================================================
// Name        : MathWorksInterview.cpp
// Author      : Jai Asher
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include "Basics.h"
#include "OOPConcepts.h"
#include <iostream>
using namespace std;

int main() {
	cout << " !!!Hello World!!!" << endl; // prints !!!Hello World!!!
	Basics b;
	Basics::staticFunction();
	b.staticFunction();
	// Static functions can be called using
	// class name as well as object name.

	b.run();

	OOPConcepts p;
	p.run();

	return 0;
}
