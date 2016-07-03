/*
 * Complex.cpp
 *
 *  Created on: Oct 5, 2015
 *      Author: Jai
 */

#include "Complex.h"

Complex::Complex(float real, float img) {
	this->real = real;
	this->img = img;

}

Complex::~Complex() {
	// TODO Auto-generated destructor stub
}


Complex Complex::operator+(Complex a) {
	Complex c(
			a.getReal() + this->getReal(),
			a.getImg() + this->getImg());
	return c;
}

