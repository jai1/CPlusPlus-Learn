#include "LinkedList.h"
#include<string.h>
#include<stdlib.h>
#include<peripherals.h>

LinkedList::LinkedList(char ch)
{
    //ctor
    head=new node(ch);
}

LinkedList::~LinkedList()
{
    //dtor
    if(head!=NULL)
        delete head;
}

LinkedList::LinkedList(const LinkedList& other)
{
    //copy ctor
    int index=0;
    char ch;
    head=NULL;
    while(1)
    {
        try
        {
            ch=other.peek(index);
        }
        catch (char  const*err)
        {
            return;
        }
        insertEnd(ch);
        index+=1;
    }
}

char  LinkedList::peek(int index) const
{
    if (head==NULL)
    {
        throw "Out of Bounds!";
    }
    node* nextNode=head;
    int i=0;
    while(nextNode!=NULL)
    {
        if(i==index)
        {
            return nextNode->data;
        }
        i+=1;
        nextNode=nextNode->next;
    }
    throw "Out of Bounds!";
}



bool LinkedList::insert(char ch,int index)
{
    if(index==0)
    {
        if (head==NULL)
            head=new node(ch);
        else
        {
            node *temp=head;
            head=new node(ch);
            head->next=temp;
        }
        return true;
    }
    int i=1;
    node* nextNode=head;// head means index 0
    while(nextNode!=NULL)
    {
        if(i==index)
        {
            node* newNode=new node(ch);
            newNode->next=nextNode->next;
            nextNode->next=newNode;
            return true;
        }
        i+=1;
        nextNode=nextNode->next;
    }
    return false;
}

bool LinkedList::insertEnd(char ch)
{
    if (head==NULL)
    {
        head=new node(ch);
        return true;
    }
    node *current=head;
    node* nextNode=head->next;
    while(nextNode!=NULL)
    {
        current=nextNode;
        nextNode=current->next;
    }
    current->next=new node(ch);
    return true;
}


bool LinkedList::remove(int index)
{
    if (head==NULL)
    {
        return false;
    }
    if(index==0)
    {
        node* temp=head;
        head=head->next;
        temp->next=NULL;
        delete temp;
        return true;
    }
    node *curNode=head;
    node* nextNode=curNode->next;
    int i=1;
    while(nextNode!=NULL)
    {
        if(i==index)
        {
            node* temp=nextNode;
            curNode->next=nextNode->next;
            temp->next=NULL;
            delete temp;
            return true;
        }
        i+=1;
        curNode=nextNode;
        nextNode=curNode->next;
    }
    return false;
}

// need 2 variables curr and next and
// the next is the node to be removed
bool LinkedList::remove(char ch)
{
    if (head==NULL)
    {
        return false;
    }
    if(head->data==ch)
    {
        node* temp=head;
        head=head->next;
        temp->next=NULL;
        delete temp;
        return true;
    }
    node *curNode=head;
    node* nextNode=curNode->next;
    int i=1;
    while(nextNode!=NULL)
    {
        if(nextNode->data==ch)
        {
            node* temp=nextNode;
            curNode->next=nextNode->next;
            temp->next=NULL;
            delete temp;
            return true;
        }
        i+=1;
        curNode=nextNode;
        nextNode=curNode->next;
    }
    return false;
}

void LinkedList::print()
{
    node *temp=head;
    printImpData("Printing Linked List Data");
    while(temp!=NULL)
    {
        cout<<temp->data<<"\t";
        temp=temp->next;
    }
}

void LinkedList::learn()
{
    printImpData("Learning to use linked lists");
    LinkedList l('a');
    l.insert('b');
    l.insert('c');
    l.insert('j');
    l.insert('d',2);
    l.print();
    l.insert('a',2);
    l.print();
    l.insert('1',200);
    l.insert('m',6);
    l.print();
    LinkedList l2(l);
    l.remove('a');
    l.remove(2);
    l.remove(100);
    l.print();
    l2.print();
    l2.reverse();
    l2.print();
    printImpData("Printing Reversed Linked list");
    l2.printReverse();
}

// Need 3 variables here
// prev, current(head), next
void LinkedList::reverse()
{
    printImpData("Reversing Linked list");
    node *nxt,*prev=NULL;
    while(head!=NULL)
    {
        nxt=head->next;
        head->next=prev;
        prev=head;
        head=nxt;
    }
    head=prev;
}


// Using Recursion
void LinkedList::printReverse(node* i_node)
{
    if(head==NULL)
        return;
    i_node=i_node?i_node:head;
    if(i_node->next!=NULL)
        printReverse(i_node->next);
    cout<<i_node->data<<"\t";
}

