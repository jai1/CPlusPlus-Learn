#include<iostream>
#include<string.h>
using namespace std;
//Creating a INTELLEGENT queue using array

#define MAX_SIZE 5
#define SUCCESS 0
class Queue
{
	int array[MAX_SIZE];
	int front;
	int rear;
	bool rearrange();
	public:
	Queue();
	void enqueue(int );
	int dequeue();
	void display();
}; 

void Queue::display()
{
	for(int temp=0;temp<(front-rear);temp++)
        {
                cout<<"\n"<<temp<<". "<<array[temp];
        }
}

bool Queue::rearrange()
{
	if(rear==0 && front==MAX_SIZE)
		return 1;
	int temp=0;
	for(;temp<(front-rear);temp++)
	{
		array[temp]=array[temp+rear];
	}
	front=temp;
	rear=0;
	cout<<"\nRearrange Helped\n";
	return 0;
}

Queue::Queue()
{
	front=0;
	rear=0;
	memset(array,0,sizeof(array));
}



void Queue::enqueue(int i_value)
{
	if(front==MAX_SIZE && rearrange()!=SUCCESS)
	{
		cout<<"\n========================================";
		cout<<"\nThe array is full";
		cout<<"\n========================================";
		return;	
	}
	array[front++]=i_value;
}

int Queue::dequeue()
{
	if(front==rear)
	{
		cout<<"\n========================================";
		cout<<"\nThe array is empty";
		cout<<"\n========================================";
		return -1;
	}
	return array[rear++];
}

int main()
{
	Queue obj;
	obj.enqueue(10);
	obj.enqueue(20);
	obj.enqueue(30);
	obj.enqueue(40);
	obj.display();
	cout<<"\nDequeued "<<obj.dequeue();
	obj.enqueue(50);
	obj.enqueue(60);
	obj.display();

	cout<<"\nDequeued "<<obj.dequeue();
	cout<<"\nDequeued "<<obj.dequeue();
	cout<<"\nDequeued "<<obj.dequeue();
	cout<<"\nDequeued "<<obj.dequeue();

	cout<<"\nDequeued "<<obj.dequeue();
	cout<<"\nDequeued "<<obj.dequeue();
	cout<<"\nDequeued "<<obj.dequeue();
	cout<<"\nDequeued "<<obj.dequeue();

	obj.enqueue(50);
        obj.enqueue(60);
	obj.enqueue(10);
        obj.enqueue(20);
        obj.enqueue(30);
        obj.enqueue(40);
        obj.display();

	return 0;
}
