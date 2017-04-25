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
