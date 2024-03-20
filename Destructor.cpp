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
        cout<<"A Destructed with i = " << i <<endl;
    }
};

A global(0);

int main() {
    A obj[] = {1,2,3};
    vector<A> vect;
    vect.push_back(A(4));
    vect.push_back(A(5));
    vect.push_back(A(6));

    // A(4) never destructed
    A* ptr1 = new A(7);
    A* ptr2 = new A(8);

    // Uncommenting below statement will not destruct 0 (global variable)
    // throw exception();
    { 
        // Deleted first since it's block ends first
        A obj(9);
    }

    // delete ptr does two things - first calls the destructor and then deallocates memory.
    delete ptr2;

    return 0;
}
