#include <iostream>

using namespace std;

int getInt() {
    int a = -10;
    return a;
}

const int& getInt2() {
    const int& t = getInt();
    cout<<"t = "<<t;
    return t;
}

int main() {

    const int& a = getInt2();
    cout<<"a = "<<a;
}

// Output
// t = -10a = 1 // Note that a is corrupted

/*
Same thing happens with shared pointer:-
#include <iostream>
#include <memory>
using namespace std;

typedef shared_ptr<int> SharedInt;

SharedInt getInt() {
    int a = -30;
    return make_shared<int>(a);
}

const SharedInt& getInt2() {
    const SharedInt& t = getInt();
    cout<<"t = "<<*t<<endl;
    return t;
}

int main() {
    const SharedInt& a = getInt2();
    cout<<"a = "<<*a<<endl;
}

// Output
// t = -10a = 1 // Note that a is corrupted


*/
