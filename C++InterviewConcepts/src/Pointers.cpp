/*
 * Pointers.cpp
 *
 *  Created on: Oct 5, 2015
 *      Author: Jai
 */

#include "Pointers.h"

Pointers::Pointers() {
	// TODO Auto-generated constructor stub

}

Pointers::~Pointers() {
	// TODO Auto-generated destructor stub
}

void Pointers::run() {
	plusPlusAssociativity();
    effectOfNew();
}

void Pointers::effectOfNew() {
    char *ptr;
    cout<<"Address of ptr(&ptr)="<<&ptr<<endl;
    cout<<"Address in ptr(ptr)="<<ptr<<endl;
    // Not Initialized
    // cout<<"Value in address in ptr(*ptr)="<<*ptr<<endl;
    cout<<"************************************"<<endl;
    char **ptr2;
    cout<<"Address of ptr2(&ptr2)="<<&ptr2<<endl;
    // Garbage
    cout<<"Address in ptr2(ptr2)="<<ptr2<<endl;
    // Not Initialized
    // cout<<"Value in address in ptr2(*ptr2)="<<*ptr2<<endl;
    cout<<"************************************"<<endl;
    ptr2 = new char*(0);
    cout<<"Address of ptr2(&ptr2)="<<&ptr2<<endl;
    cout<<"Address in ptr2(ptr2)="<<ptr2<<endl;
    // Not Initialized
    // cout<<"Value in address in ptr2(*ptr2)="<<*ptr2<<endl;
    cout<<"************************************"<<endl;
    *ptr2 = ptr;
    cout<<"Address of ptr2(&ptr2)="<<&ptr2<<endl;
    cout<<"Address in ptr2(ptr2)="<<ptr2<<endl;
    cout<<"Value in address in ptr2(*ptr2)="<<*ptr2<<endl;
    cout<<"************************************"<<endl;
    ptr = new char('c');
    cout<<"Address of ptr(&ptr)="<<&ptr<<endl;
    cout<<"Address in ptr(ptr)="<<ptr<<endl;
    // Not Initialized
    cout<<"Value in address in ptr(*ptr)="<<*ptr<<endl;
    cout<<"************************************"<<endl;
    *ptr2 = ptr;
    cout<<"Address of ptr2(&ptr2)="<<&ptr2<<endl;
    cout<<"Address in ptr2(ptr2)="<<ptr2<<endl;
    cout<<"Value in address in ptr2(*ptr2)="<<*ptr2<<endl;
    cout<<"Value in address in *ptr2(**ptr2)="<<**ptr2<<endl;
    cout<<"************************************"<<endl;    
}

void Pointers::plusPlusAssociativity() {
	char *ptr = "New Array";
	cout<<*ptr++<<endl;
	cout<<*ptr<<endl;

	// Output -> "Ne"
	/* Explanation:-
		*ptr++ => *ptr in this operation and then
				  ptr++ for the next instruction.
		Hence the 2nd cout gives "e".
	*/
}
