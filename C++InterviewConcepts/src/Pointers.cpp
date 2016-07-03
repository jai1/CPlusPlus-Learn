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
