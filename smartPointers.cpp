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
