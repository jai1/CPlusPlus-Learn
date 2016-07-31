#include<iostream>
#include<string>

using namespace std;

/* For Binary Operator
Syntax:-

<Class on which it is called> operator <parameter>

For 

<parameter> operator  <Class on which it is called>
Use friend

This is reverse of Unary Operator

*/


class A {
    string name;
    int value;
    public:
    A(string name, int value) {
        this->value = value;
        this->name = name;
    }
    
    void print() {  
        cout<<"Name = "<<name<<" value = "<<value<<endl;
    }

    A operator+(int val) {
        return A("obj2", val + value);   
    }

    // Error since this is ambiguous with A operator+(int val)
    // friend A operator+(A &obj, int val);

    friend A operator+(int val, A &obj);
};

A operator+(int val, A &obj) {
    return A("obj3", val + obj.value);
}

int main() {
    A obj("obj1", 10);
    A res = obj + 100;
    // Needs friend function 
    A res2 = 200 + obj;
    obj.print();
    res.print();
    res2.print();
    return 0;
}
