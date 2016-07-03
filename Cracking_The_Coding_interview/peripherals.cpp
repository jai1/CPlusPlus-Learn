#include<iostream>
using namespace std;

void printHeader(const char *data)
{
    cout<<"\n*******************************************";
    cout<<"\n"<<data;
    cout<<"\n*******************************************";
    cout<<endl;
}

void printError(const char* data)
{
    cout<<"\n++++++++++++++++++++";
    cout<<"\nERROR: "<<data;
    cout<<"\n++++++++++++++++++++";
    cout<<endl;
}

void printImpData(const char *data)
{
    cout<<"\n----------";
    cout<<"\n"<<data;
    cout<<"\n----------";
    cout<<endl;
}

void printArray(int arr[],size_t size)
{
    printImpData("Printing Array");
    for(int i=0;i<size;i++)
    {
        cout<<arr[i]<<" ";
    }
}

void swap(int *a, int *b)
{
        int t = *a;
        *a = *b;
        *b = t;
}
