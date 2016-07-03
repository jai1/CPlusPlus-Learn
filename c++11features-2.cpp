#include<iostream>
using namespace std;


class A {
public:
	int memeber = 0; // in class initializer

	A(char *val) {
		cout << "Constructor with char pointer called" << endl;
	}
	
	A(int val) {
		cout << "Constructor with int value called" << endl;
	}
	
	A() = default; // to have default constructor for A
	
	virtual int func1() {
	
	}
	
	char func2() {
		
	}
	
	virtual int func3() {
	
	}
	

    virtual int func4() final {
	
	}

	/*
	// Only virtual functions can be final
    int func5() final {
	
	}
	*/
	
};


class B : public A {
	public:
	
	B(char a) = delete; // to prevent type conversion of char to int
	
	B(int a) : B() { 
		// one constructor calls other and if after executing entire chain no constructor of A is called then the default constructor is called
		cout << "Constructed B with value " << a << endl;
	}
	
	B() {
		cout << "Constructed B" << endl;
	}

	int func1() override {
		// override keyword for make overriding compulsory
		return 0;
	}
	

	/*
	// override prevents 2 versions of functions to exists one in base and other in inherited - if you forgot to use virtual function
	char func2() override {
	
	}
	*/

	
	/* 
	//override prevents incorrect data type between the base and inherited class
	char func3() override{
	
	}
	*/
	
	/*
	// Can't try to overload a function marked as final
	int func4() {
		
	}
	*/
};

template <class T> constexpr T square(T val) {
	return val * val;
}	


enum CarsOld {Audi, BMW};
enum FruitsOld {Orange, Banana};

// C++11 introduced class for enums to avoid comparison between 2 different enums 
enum class CarsNew {Audi, BMW};
enum class FruitsNew {Orange, Banana};

int main() {
	// A(NULL); // Ambiguous function call since NULL == 0
	A(nullptr); // This redirects to proper function - A(char* val)
	
	cout << (CarsOld::Audi == FruitsOld::Orange) << endl; // Wrong
	// cout << (CarsNew::Audi == FruitsNew::Orange) << endl; // generates error // Right
	
	static_assert(sizeof(int) == 4, "Error Size of int is not 4 bytes"); // compile time static asserts
	
	B(10);
	
	// B('B'); // errors out due to delete 
	
		cout << square<int>(3) << endl;// compile time calculations
	
	int x = 5;
	
	// lambda with stack members from calling function
	cout << [&] (int y)  -> long // return type 
	{
		return x * y;
	} (4) << endl;
	
	
	return 0;
}
