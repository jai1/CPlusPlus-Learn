#include "QuickSort.h"
#include <peripherals.h>
#include <time.h>
#include <stdlib.h> //Library for srand and ran

/*
    Key features:-
        a. Quick sort does in place swaps. Merge sort requires extra O(n) space to temporarily save
        the newly sorted array.
        b. Quick sort is not O(nlogn) to base 2 since unlike merge sort we don't divide the array
        into 2 parts.
        c. Choosing the pivot point is key because for eg if we always choose the first point to
        be the pivot point then the time take to sort is n-1 + n-2 + n-3 + .......
        d. Hence choosing a pivot swings the execution time from O(n^2) and O(nlogn)
        O(n^2) -> worst case least element as pivot
        O(nlogn) -> best case -? median element
        e. As per the videos choosing an random pivot gives execution time to O(nlogn)
*/

QuickSort::QuickSort()
{
    //ctor
}

QuickSort::~QuickSort()
{
    //dtor
}

void QuickSort::learn()
{
    srand(time(0));
    int size=20;
    int a[size];
    srand(1);
    for(int i=0;i<size;i++)
        a[i]=rand()%200;
    printImpData("Print Before Quick sorting");
    printArray(a,size);
    sort(a,0,19);
    printImpData("Print after sorting");
    printArray(a,size);
}

int QuickSort::choosePivotElement(int size)
{
    return rand()%size;
}

void QuickSort::sort(int a[],int beg,int end)
{
    if(beg>=end)
        return;
    // i is the barrier which separates the element<=pivotElement
    // form elements>pivotElement
    int i=beg+1;
    int position=choosePivotElement((end - beg)+1);
    int pivotElement=a[beg+position];
    // As of now assume position to be 0 and pivotElement to be a[beg]
    //hence i starts from 1
    swap(&a[beg],&a[beg+position]);
    for(int j=i;j<=end;j++)
    {
        if(a[j]<=pivotElement)
        {
            swap(&a[i],&a[j]);
            i++;
        }
    }
    swap(&a[beg],&a[i-1]);
    /*
    Invariant -> pivot element is in it;s correct position
    All elements before pivotElement are less or equal to the
    pivotElement.
    All elements before pivotElement are greater than the
    pivotElement.
    */
    //printArray(a,19);
    sort(a,beg,i-2);
    sort(a,i,end);
}
