/*
 * Complex.h
 *
 *  Created on: Oct 5, 2015
 *      Author: Jai
 */
#include <iostream>
#include <string>
using namespace std;

#ifndef COMPLEX_H_
#define COMPLEX_H_

class Complex {
private:
		float real, img;
public:
	Complex(float real, float img);
	virtual ~Complex();
	Complex operator+(Complex a);

	friend std::ostream& operator<<(std::ostream&, Complex );

	float getImg() const {
		return img;
	}

	void setImg(float img) {
		this->img = img;
	}

	float getReal() const {
		return real;
	}

	void setReal(float real) {
		this->real = real;
	}
};

#endif /* COMPLEX_H_ */
