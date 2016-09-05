
#include<iostream>
using namespace std;

//stack using 1 way linked list
struct node
{
	int value;
	node *prev;
	node();
};

node::node()
{
	value=0;
	prev=NULL; //reverse linked list
}

class Stack
{
	int m_size; // size of stack
	node* m_head;
	node* m_tail;
	//the head will be constant and the stack will expand at the tail
	public:
	int getSize();
	void push(int);
	bool pop();
	void display();
	Stack();
	~Stack();
	void destroy();
};
Stack::Stack()
{
	m_head=NULL;
	m_tail=NULL;
	m_size=0;

}

Stack::~Stack()
{
	destroy();
}

void Stack::destroy()
{
	if(m_size==0)
		cout<<"\nCan't Destroy as Stack is empty";
	node* temp=m_tail;
	while(m_size)
	{
		m_size--;
		delete temp;
		temp=temp->prev;
	}
}

int Stack::getSize()
{
	return m_size;
}

void Stack::push(int data)
{
	node *temp=new node;
	temp->value=data;
	if(m_tail==NULL)
		m_tail=temp;
	else
	{
		temp->prev=m_tail;
		m_tail=temp;
	}
	m_size++;
}

bool Stack::pop()
{
	if(m_size==0)
		return 1; // Stack is empty
	node *temp=m_tail;
	m_tail=m_tail->prev;
	delete temp;
	m_size--;
}

void Stack::display()
{
	if(!m_size)
		cout<<"\nStack is empty";
	int size=m_size;
	node* temp=m_tail;
	while(size)
	{
		size--;
		cout<<"\n"<<size<<". "<<temp->value;
		temp=temp->prev;
	}
}

int main()
{
    Stack stack;
    stack.display();
    cout<<"\nstack.pop returned "<<stack.pop();
    stack.push(1);
    stack.push(10);
    stack.push(12);
    stack.push(21);
    stack.display();
    cout<<"\nstack.pop returned "<<stack.pop();
    cout<<"\nNow the size of stack is "<<stack.getSize();
    cout<<"\nstack.pop returned "<<stack.pop();
    stack.display();
	return 0;
}
