/*
    scoped_ptr - fastest
    unique_ptr - fast - copy of unique_ptr moves the ownership
    shared_ptr - slow and can result in cyclic reference
               - A has shared pointer to B and B has shared pointer to A
               - this leads to A and B never deleted
               - use weak pointer or references to avoid this   
    weak_ptr - need to call lock() to get the data
             - lock upgrades the weak_ptr to shared_ptr if object is not deleted, else exception. In order to avoid exception check for isExpired.

*/
#include<iostream>
#include<boost/shared_ptr.hpp>
#include<boost/make_shared.hpp>
#include<boost/weak_ptr.hpp>
using namespace std;

int main() {
	// Program 1
	boost::shared_ptr<int> sharedPtr = boost::make_shared<int>(10);
	boost::weak_ptr<int> weakPtr = sharedPtr;
	cout<<*weakPtr.lock()<<endl; // prints 10 since weak_ptr points to sharedPtr

	boost::shared_ptr<int> sharedPtr2 = weakPtr.lock();
	sharedPtr2.reset();
	cout<<weakPtr.lock()<<endl; // weakPtr is still valid since sharedPtr is not destroyed

	weakPtr.reset();
	cout<<weakPtr.lock()<<endl; // Now weakPtr points to null


	// Program 2
	sharedPtr2 = sharedPtr;
	weakPtr = sharedPtr2;
	sharedPtr2.reset();
	cout<<weakPtr.lock()<<endl; // weakPtr is still valid since sharedPtr is not destroyed
	return 0;
}

