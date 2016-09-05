#include<iostream>
using namespace std;

int main()
{
    char b='B';
    char a='A';
/* Pointer to a const used frequently*/
    //Declaration 2
    const char *ptr=&a;
    ptr=&b;
    /*Value of pointer can change but the valeu in the variable it points to can't, eventhough a is not a constant
    */
    //*ptr='J'; -- illegal decelaration

    //Declaration 2
    char const *ptr1=&a;
    ptr1=&b;
/* Const Pointer. the pointer cant point to anything else*/
    char *const ptr2=&a;
    *ptr2='J';
    //ptr2=&b; -- illegal decelaration

/* Const Pointer to a const. the pointer cant point to anything else
    OR
    change the value of the variable it is pointing to
*/
    const char *const ptr3=&a;
    //*ptr2='J';-- illegal decelaration
    //ptr3=&b;-- illegal decelaration
    return 0;
}
