#include<iostream>
using namespace std;

struct node
{
	node();
	float value;
	node *next;
};

/* In this program we used a single sided Linked List i.e each member has access to only it's next Member.
In this case we had to handle all operations sitting on the previous node, hence special handling was required for m_root as it has no previous node.
For ease of access we use a double sided linked list, where each node has info on the next node as well as previous node. But maintaining so many pointers becomes difficult.
*/
node::node()
{
	value=0;
	next=NULL;
}
class LinkedList
{
	node *m_root;
	public:
	void insertNode(float ,short );
	bool deleteNode(float );
	bool deleteNode(short );
	short size();
	bool setValue(float ,short );
	float getValue(short );
	void destroy();
	void display();
	LinkedList();
	~LinkedList();
};

void LinkedList::display()
{
	if(m_root==NULL)
        {
	        cout<<"\nThe Linked List is empty";
		return;
	}
	node *tempNode=m_root;
        short o_size=0;
        do
        {
		cout<<"\n The value at "<<o_size<<" is "<<tempNode->value;
		tempNode=tempNode->next;
		o_size++;
        }while(tempNode != NULL);

}
bool LinkedList::setValue(float i_newValue,short position)
{
	if(m_root==NULL)
	{
                cout<<"\nThe Linked List is empty";
                return 1;
	}
	node *tempNode=m_root; 
	short o_size=1;
        while(tempNode->next != NULL)
        {
                if(o_size++==position)
                {	
			tempNode->next->value=i_newValue;
                        return 0;
                } 
                tempNode=tempNode->next;
        }
        cout<<"\nThe linked list is shorter than "<<position;
        return -1;

}

float LinkedList::getValue(short position)
{
	if(m_root==NULL)
	{
		cout<<"\nThe Linked List is empty";
		return -1;
	}
	node *tempNode=m_root;
	short o_size=1;
        while(tempNode->next != NULL)
        {
                if(o_size++==position)
		{
			return tempNode->next->value;
		}	
                tempNode=tempNode->next;
        }
	cout<<"\nThe linked list is shorter than "<<position;
        return -1;
}

short LinkedList::size()
{
	if(m_root==NULL)
		return 0;
	node *tempNode=m_root;
	short o_size=1;
	while(tempNode->next != NULL)
	{
		o_size++;
		tempNode=tempNode->next;
	}
	return o_size;
}


bool LinkedList::deleteNode(short i_position)
{
	node *prevNode=m_root,*tempNode=m_root->next;
	short position;
        if(m_root==NULL)
                return 1;
        if(m_root->next==NULL)
        {
                if(i_position==0)
                {
                        delete m_root;
                        m_root=NULL;
                        return 0;
                }
                else
                        return 1;
        }
        else if(i_position==0)
	{
		delete m_root;
		m_root=tempNode;
		return 0;
	}
	else
        {
		bool deleted=0;
		do
                {
			position++;
                        if(position==i_position)
                        {
                        	deleted=1;
			        prevNode->next=tempNode->next;
                                delete tempNode;
                        }
                        prevNode=tempNode;
                        tempNode=tempNode->next;
                }while(tempNode != NULL);
		if(deleted==true)
			return 0;
		else
			return 1;
        
	}
}

bool LinkedList::deleteNode(float i_value)
{
	node *prevNode=m_root,*tempNode=m_root->next;
	bool deleted=0;
	if(m_root==NULL)
		return 1;
	if(m_root->next!=NULL)
		tempNode=m_root->next;
	else 
		tempNode=m_root;	
	//delete consequetive starting nodes having this value
	while(prevNode->value==i_value)
	{
		delete m_root;
		if(tempNode!=prevNode)
		{
			m_root=tempNode;
			prevNode=tempNode;
			if(tempNode->next!=NULL)
				tempNode=tempNode->next;
		}
		else
			return !deleted;
		deleted=1;
	}

	do
	{
		if(tempNode->value==i_value)
		{
			deleted=1;
			prevNode->next=tempNode->next;
			delete tempNode;
		}
		prevNode=tempNode;
		tempNode=tempNode->next;
	}while(tempNode != NULL);
	if(deleted==true)	
		return 0;
	else
		return 1;
}

LinkedList::LinkedList()
{
	m_root=NULL;
}

LinkedList::~LinkedList()
{
	destroy();
}

void LinkedList::destroy()
{
	node *tempNode=m_root;
	while(tempNode!=NULL)
	{
		m_root=tempNode;
		tempNode=tempNode->next;
		delete m_root; 
	}
	m_root=NULL;
}

void LinkedList::insertNode(float i_value,short i_position=0)
{
	short position=1;
	if(m_root==NULL)
	{
		m_root=new node;
		m_root->value=i_value;
		return;
	}
	node *tempNode=m_root->next,*prevNode=m_root;
	if(i_position==0)
	{
		m_root=new node;
		m_root->value=i_value;
		m_root->next=prevNode;
		return;
	}
	
	while(tempNode!=NULL && position!=i_position)
	{
		prevNode=tempNode;	
		tempNode=tempNode->next;
		position++;
	}
	if(tempNode==NULL)
	{
		tempNode=new node;
		tempNode->value=i_value;
		prevNode->next=tempNode;
	}
	else
	{
		node *newNode=new node;
		newNode->value=i_value;
		prevNode->next=newNode;
		newNode->next=tempNode;
	}
}

int main()
{
	LinkedList linkedList;
	
	linkedList.display();
	
	linkedList.insertNode(10);
	linkedList.insertNode(20);
	//by default it will insert at position 0 i.e root 
	linkedList.insertNode(3);
	linkedList.insertNode(20);
	
	linkedList.insertNode(200,2);
	
	cout<<"\nSize of Linked List is "<<linkedList.size();
	linkedList.display();

	cout<<"\n============================================\n";	
	cout<<"\nValue at position 3 is "<<linkedList.getValue(3);
	cout<<"\nChanging Value at position 3 to 5";
	linkedList.setValue(5,3);
	linkedList.display();	
	cout<<"\n============================================\n";
	cout<<"deleting value at node 0 and inserting 20 at node 4";
	linkedList.deleteNode((short)0);
	linkedList.insertNode(20,4);
	linkedList.display();

	cout<<"\n============================================\n";
	cout<<"delete all occurences of 20 and insert 7 at 0";
	linkedList.deleteNode((float)20);
	linkedList.insertNode(7,0);
	linkedList.display();
	
	cout<<"\n============================================\n";
	cout<<"Destroy Linked List";
	linkedList.destroy();
	linkedList.display();
	return 0;
}
