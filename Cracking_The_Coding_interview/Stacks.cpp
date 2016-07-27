#include "Stacks.h"

Stacks::Stacks(int size)
{
    // Since index 0 s a valid index the top should be initialized with -1
    top=-1;
    curSize=size;
    start=new int[curSize];
}

Stacks::~Stacks()
{
    //dtor
}

void Stacks::push(int data)
{
    top+=1;
    if(top>=curSize)
    {
        int *temp=new int[curSize*2];
        memcpy(temp,start,curSize*sizeof(int));
        curSize*=2;
        delete[] start;
        start=temp;
    }
    *(start+top)=data;

}

int  Stacks::peek(int index)
{
    if (index == -1)
        index=top;
    if (top == -1 || top - index <0)
        throw "Out of bounds";
    return *(start+index);
}

void Stacks::print()
{
    int i=0;
    printImpData("Printing Stacks");
    while(1)
    {
        try
        {
            cout<<peek(i)<<"\t";
        }
        catch(const char*err)
        {
            return;
        }
        i+=1;
    }
}

bool Stacks::pop()
{
    if(top==-1)
        return false;
    top-=1;
    return true;
}

void Stacks::learn()
{
    Stacks st;
    st.push(10);
    st.push(20);
    st.push(30);
    st.push(20);
    st.pop();
    st.push(40);
    st.print();
    st.push(50);
    st.push(60);
    st.push(70);
    st.push(80);
    st.push(90);
    st.push(100);
    st.push(110);
    st.push(120);
    st.print();
}

bool Stacks::isEmpty()
{
    if(top==-1)
        return true;
    return false;
}

int Stacks::size()
{
    return top+1;
}
