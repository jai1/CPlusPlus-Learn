#include<iostream>

using namespace std;


class A {
	private:
	// public:
	class B {
		public:
		B() {
			cout<<"B Constructed"<<endl;
			// Compilation Fails since in C++ inner class doesn't have implicit access to outer class variables
			// Inner class is a friend of outer class so you can just give a reference of outer class
			// while creating the inner class and access the variables through that reference.
			// cout<<"a="<<a;
		}
	};

	public:
	int a;
	B innerObj;
	A() {
		a =10;
	}
};

class C {
	public:
	// Fails since B is a private definition of A
	// just uncomment the public on line 8
	// A::B obj;
};

int main() {
	A obj;
	return 0;
}
