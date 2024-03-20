#include <iostream>

using namespace std;

int getInt() {
    int a = -10;
    return a;
}

// Return By Reference is Evil, unless you are a 100% sure that the lifetime of the object won't end after the function call.
// In General avoid it.
// https://stackoverflow.com/questions/752658/is-the-practice-of-returning-a-c-reference-variable-evil
const int& getInt2() {
    const int& t = getInt();
    cout<<"t = "<<t<<endl;
    return t;
}

int main() {
    const int& a = getInt2();
    cout<<"a = "<<a<<endl;
}

// Output
// t = -10
// a = 1 // Note that a is corrupted

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
