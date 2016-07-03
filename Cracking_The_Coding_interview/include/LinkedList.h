#include <iostream>
using namespace std;
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

struct node
{
    node* next;
    char data;
    node(char ch)
    {
        next=NULL;
        data=ch;
    }
    node()
    {
        next=NULL;
        data='\0';
    }
    ~node()
    {
        if(next!=NULL)
            delete next;
    }
};

class LinkedList
{
    public:
        /** Default constructor */
        LinkedList(char ch='\0');
        /** Default destructor */
        ~LinkedList();
        /** Copy constructor
         *  \param other Object to copy from
         */
        LinkedList(const LinkedList& other);
        bool insert(char ch,int index=0);
        bool insertEnd(char );
        bool remove(char ch);
        bool remove(int index);
        char peek(int index) const;
        void print();
        static void learn();
        void reverse();
        void printReverse(node* i_node=NULL);
    protected:
        node* head;
    private:

};

#endif // LINKEDLIST_H
