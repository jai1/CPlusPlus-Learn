#include<vector>
#include<iostream>

using namespace std;

class A {
    int i;
    public:
    A(int i) {
        this->i = i;
        cout<<"A Constructed with i = "<< i <<endl;
    }
    ~A() {
        cout<<"A Desructed with i = " << i <<endl;
    }
};

A global(7);

int main() {
    A obj[] = {-1,-2,-3};
    vector<A> vect({1, 2, 3});
    // A(4) never destructed
    A* ptr1 = new A(4);
    A* ptr2 = new A(5);

    // Uncommenting below statement will not destruct 7
    // throw exception();
    { 
        // Deleted first since it's block ends first
        A obj(100);   
    }

    // delete ptr doestwo things - deallocate memory and call destructor
    delete ptr2;

    return 0;
}
