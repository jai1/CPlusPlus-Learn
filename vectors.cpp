#include<iostream>
#include<vector>
using namespace std;

class A {
	
	public:
	int a;	
	A() {
		cout<<"Constructor of A called"<<endl;
	}

	A(int a):a(a) {
		cout<<"Parameterized constructor of A called with value "<<a<<endl;
	}
	
	A(const A &obj) {
		a = obj.a;
		cout<<"Copy constructor called"<<endl;
	}	
	A& operator=(const A& arg)
	{
			
    		a = arg.a;
		cout<<"Assignment operator called a = "<<a<<endl;
		cout<<"arg.a = "<<arg.a<<endl;
		return *this;
	}
	
}; 


int main() {
	vector<A> lst(4);
	vector<A> lst2(10,A(3));
	
	cout<<"+++++++++++++++++++++++++++++++++++++++++"<<endl;
	cout<<"lst size = "<<lst.size()<<endl;
        cout<<"+++++++++++++++++++++++++++++++++++++++++"<<endl;
	lst.push_back(A(10));
        cout<<"+++++++++++++++++++++++++++++++++++++++++"<<endl;
        cout<<"new lst size = "<<lst.size()<<endl;
        cout<<"+++++++++++++++++++++++++++++++++++++++++"<<endl;	
	lst.reserve(100);
        cout<<"+++++++++++++++++++++++++++++++++++++++++"<<endl;
        cout<<"new lst size = "<<lst.size()<<endl;
        cout<<"+++++++++++++++++++++++++++++++++++++++++"<<endl;
	
	cout<<"+++++++++++++++++++++++++++++++++++++++++"<<endl;
	cout<<"lst2 size = "<<lst2.size()<<endl;
	cout<<"+++++++++++++++++++++++++++++++++++++++++"<<endl;
	for(vector<A>::iterator it = lst2.begin(); it != lst2.end(); it++) {
		cout<<it->a<<endl;
	}
	cout<<"+++++++++++++++++++++++++++++++++++++++++"<<endl;
	lst2[0]=4;
	cout<<"+++++++++++++++++++++++++++++++++++++++++"<<endl;
	for(vector<A>::iterator it = lst2.begin(); it != lst2.end(); it++) {
                cout<<it->a<<endl;
        }
 	cout<<"+++++++++++++++++++++++++++++++++++++++++"<<endl;
	lst2[1].a=5;
        lst2[2] = lst2[0];
	cout<<"+++++++++++++++++++++++++++++++++++++++++"<<endl;
        for(vector<A>::iterator it = lst2.begin(); it != lst2.end(); it++) {
                cout<<it->a<<endl;
        }
        cout<<"+++++++++++++++++++++++++++++++++++++++++"<<endl;
	return 0;
}
