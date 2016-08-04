#include<iostream>
#include<string>

using namespace std;

static int counter=0;

template <typename T, int size, long id>
class A {
	public:
	class B {
		public:
		B() {
			// __PRETTY_FUNCTION__ is used to print the parameters
			cout<<"Class B() "<< __PRETTY_FUNCTION__ <<endl;
		}
		void incrementData() {
			counter++;
		}
	};
	static B t;
	void incrementData() {
		t.incrementData();
	}
};

// This line is to define static variable
// typename needs to be specially used with template - special need
template <typename T, int size, long id>
typename A<T, size, id>::B A<T, size, id>::t;

int main() {
	A<int, 10, 0> a;
	A<int, 10, 0> b;
	A<int, 10, 1> c;
	a.incrementData();
	b.incrementData();
	c.incrementData();
	return 0;
}

