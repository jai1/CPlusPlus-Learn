#include <iostream>
#include <peripherals.h>
using namespace std;

// O(nlog n)
namespace mergeSort
{
    void mergeSort(int a[],size_t begin, size_t end)
    {
        // Base Case
        if(begin>=end)
            return;
        size_t mid = int((begin + end)/2);
        // Divide the problem into sub problem
        mergeSort(a,begin,mid);
        mergeSort(a,mid+1,end);
        // Now merge the 2 lists
        int b[end - begin + 1];
        for(int i=begin,j=mid+1,k=0; i<=mid || j<=end; k++)
        {
        //look in inversion solution for cleaner if conditions
            if((a[i]>a[j] && j<=end) || i>mid)
            {
                b[k]=a[j];
                j++;
            }
            else
            {
                b[k]=a[i];
                i++;
            }
        }
        for(int i=0; i<=end - begin ; i++)
            a[i+begin]=b[i];
    }

    // Inversions => A[i] > A[j] for i<j
    // EFFECT: Modifies (sorts) i/p array (a)
    int countInversions(int a[],size_t begin, size_t end)
    {
        if(begin>=end)
            return 0;
        size_t mid=(begin+end)/2;
        int left=countInversions(a,begin,mid);
        int right=countInversions(a,mid+1,end);
        int split=0;
        //Sorting and counting the number of split inversions
        int b[end - begin + 1];
        for(int i=begin,j=mid+1,k=0; i<=mid || j<=end; k++)
        {
            if(j>end)
            {
                b[k]=a[i];
                i++;
            }
            else if(i>mid)
            {
                b[k]=a[j];
                j++;
            }
            else  if(a[i]>a[j])
            {
                b[k]=a[j];
                j++;
                split+=(mid-i)+1;
            }
            else
            {
                b[k]=a[i];
                i++;
            }
        }
        for(int i=0; i<=end - begin ; i++)
            a[i+begin]=b[i];
            // a[]  is equivalent to *a we are modifying a here
        return (left + right +split);
    }

    void learn()
    {
        printHeader("Learning MergeSort");
        int a[10]={-1,100,10,43,12,92,-2,101,1000,0.2};
        printImpData("Data before sorting");
        for(int i=0; i<10; i++)
            cout<<a[i]<<"\t";
        mergeSort(a,0,9);
        printImpData("Data after sorting");
        for(int i=0; i<10; i++)
            cout<<a[i]<<"\t";
        printHeader("learning to count inversions");
        int b[10]={10,9,1,2,3,4,5,6,7,8};
        // inversions = 9 + 8 = 17
        printImpData("Data before inversion");
        for(int i=0; i<10; i++)
            cout<<b[i]<<"\t";
        cout<<"Number of inv="<<countInversions(b,0,9);
        printImpData("Data after counting inversions & sorting");
        for(int i=0; i<10; i++)
            cout<<b[i]<<"\t";
    }

}
