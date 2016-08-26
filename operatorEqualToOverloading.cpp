#include <iostream>
#include <cassert>

using namespace std;

class A {
    protected:
    int a;
    public:
        A (int a) : a(a) {}
        bool operator==(const A& obj) {
            return a == obj.a;
        }
};


class B : public A {
    int b;
    public:
    B(int b) : A(10), b(b) {}
};

int main() {
    A a1(10), a2(5), a3(10);
    B b1(10), b2(5), b3(10);
    assert(a1 == a3);
    assert(!(a1 == a2));
    assert(b1 == b3);
    assert(b1 == b2);
    // This fails since == now calls only base class == (since A& can take B object) and hence only compares the B.a and not B.b
    // To prevent this, just override the == operator in B
    assert(!(b1 == b2));
    cout<< "Finished"<<endl;
}
