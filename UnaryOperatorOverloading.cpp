#include<iostream>

using namespace std;

/* For Unary operator:-
Syntax:-
<operator> Class;

For
Class<operator>
 turn it into a binary function
*/

class A {
    public:
        void operator++() {
            cout<<"Version 1 Called"<<endl;
        }

        void operator++(int ignored) {
            cout<<"Version 2 Called"<<endl;
            cout<<"param = "<<ignored<<endl;
        }
};

int main() {
    A obj;
    ++obj;
    obj++;
}
