/*
 * Basics.cpp
 *
 *  Created on: Oct 5, 2015
 *      Author: Jai
 */

#include "Basics.h"
#include "Pointers.h"

Basics::Basics() {
	// TODO Auto-generated constructor stub

}

Basics::~Basics() {
	// TODO Auto-generated destructor stub
}

void Basics::run() {
	for(int i=0; i<5; i++)
		functionWithStaticVariable();

	Pointers p;
	p.run();

	learnEnums();

	info();
}

void Basics::learnEnums() {
	enum COLOR { yellow, red, green = 0, blue, pink};
	cout<<COLOR::yellow<<endl; // 0
	cout<<COLOR::red<<endl; // 1
	cout<<COLOR::green<<endl; //0
	cout<<COLOR::blue<<endl; //1
	cout<<COLOR::pink<<endl; //2
	cout<<(COLOR::yellow == COLOR::green) <<endl;
	// 1 -> True
	// Thus assigning a value to an enum leads to
	// duplicates.
}



void Basics::info() {
	cout<<"Static global variable are local to the files in which they are defined."<<endl;
}

void Basics::functionWithStaticVariable() {
	static int count = 0;
	cout<<"Called "<<count++<<" Number of Times!!!"<<endl;
}


void Basics::staticFunction() {
	cout<<"Called a static function"<<endl;
}
