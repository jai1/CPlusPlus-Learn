#include <binaryTrees.h>
/*
    Can be implemented as a Binary Tree or an Array.
    Structure:-
        First fill left child then right.
        It's a Complete binary tree.
        Two types of Heap
        Max Heap - Any parent >= Child - Max value at root
        Min Heap - Any parent <= Child - Min value at root

        Note:-  In Min Heap the node needs to be greater than the parent,
                but it can be less than it's Uncle (i.e parents siblings).
                Like in the last print of Binary Tree

        Examples are on Min heap using Arrays:-
            Procedure to add an element:-
                - Add in the left most available node - for Completeness
                - Position the element
*/

/*
    Storing a Binary tree in an array:-
        a[n] is the parent of a[2n+1] and a[2n+2]
        a[n] is the child of a[ceil((n+1)/2)-1]

*/
namespace heapUsinArrays
{

    void printBinaryTreeArray(int* node, size_t heapsize)
    {
        int level=0;
        for(int i=0; i<heapsize;i++)
        {
            if(i==pow(2,level)-1)
            {
                level++;
                cout<<endl;
            }
            cout<<*(node+i)<<"\t";
        }
    }

    // Pre condition is that a and b can't point to the same memory location
    // Else both will be made 0 because of the second statement
    // Playing with pointers is dangerous
    void swap(int* a, int* b)
    {
        *a = *a + *b;
        *b = *a - *b;
        *a = *a - *b;
    }

    // In this version we just keep swapping till the node has reached the destination
    // One step per loop
    void positionNode(int *a, size_t nodeLocation)
    {
        size_t temp,temp2;
        bool swapped = true;
        temp=temp2=nodeLocation;
        while(swapped == true)
        {
            swapped=false;
            temp2=temp;
            if (temp2!=0)
                temp=int(ceil((temp+1)/2))-1;
            else
                break;
            if(temp>=0 && *(a+temp2)<*(a+temp) && temp != temp2)
            {
                swapped=true;
                swap((a+temp2),(a+temp));
            }
        }
    }

    void siftDown(int *heap,int index,size_t heapSize)
    {
        if(index>=heapSize-1)
            return;
        int leftIndex=(2*index)+1;
        int rightIndex=(2*index)+2;
        int swapIndex=0;
        //If rightIndex  > heapSize -1 then the node has either:-
        // a. left child only
        // b. No child
        if(rightIndex>heapSize-1)
        {
            // Checking for no child
            if(leftIndex>heapSize-1)
                return;
            swapIndex=leftIndex;
        }
        else
        {
            if(*(heap+rightIndex)<*(heap+leftIndex))
                swapIndex=rightIndex;
            else
                swapIndex=leftIndex;
        }
        // Keep swapping and sifting down till possible
        if(*(heap+swapIndex)<*(heap+index))
        {
            swap((heap+swapIndex),(heap+index));
            siftDown(heap,swapIndex,heapSize);
        }
    }


    // in Heap sort we delete the min node from a heap (root)
    // Logic:- Delete the root node, copy the last element to the root node
    //         and siftDown the element.
    // Reasoning:- We can't siftUp one of the child's for the root node
    //             recursively, as this will destroy the completeness of the
    //             heap. Hence we use the siftDown approach.
    // Remember that last node is at heapSize-1 and not heapSize since heapSize
    // starts from 1 and not 0
    size_t deleteMin(int *heap, size_t heapSize)
    {
        if(heapSize==1)
            return 0;
        *(heap+0)=*(heap+heapSize-1);
        heapSize--;
        siftDown(heap,0,heapSize);
        return heapSize;
    }


    // a is the name of the array which stores the heap
    // nodeLocation is the position of the value that needs to be positioned
    // Precondition -- the elements in a till nodeLocation - 1 are arranged
    // as a heap
    // Working
    void positionNode_v1(int *a, size_t nodeLocation)
    {
        size_t temp,temp2;
        // Once the desired node is placed, it needs to be swapped with an
        // existing node, but now we have one more problem i.e we now need to
        // place the existing node.
        while(true)
        {
            bool swapped = true;
            temp=nodeLocation;
            temp2=nodeLocation;
            while(swapped == true)
            {
                swapped=false;
                temp2=temp;
                if (temp2!=0)
                    temp=int(ceil((temp+1)/2))-1;
                else
                    break;
                if(temp>=0 && *(a+nodeLocation)<*(a+temp))
                    swapped=true;
            }
            if (temp2!=nodeLocation)
                swap((a+temp2),(a+nodeLocation));
            else
                //No more swaps are possible hence all problems and sub problems
                //are solved.
                break;
        }
    }

    // The new value will be inserted at a[heapSize]
    // and the increased heapSize will be increased
    size_t insert(int* a, size_t heapsize,int i_value)
    {
        *(a+heapsize)=i_value;
        positionNode(a,heapsize);
        heapsize++;
        return heapsize;
    }

    void learn()
    {
        int* a=new int[100];
        size_t heapsize=0;

        int tmp[8]={2,11,12,111,112,121,122,1111};
        memcpy(a,tmp,sizeof(tmp));
        heapsize=8;
        printBinaryTreeArray(a,heapsize);
        heapsize=insert(a,heapsize,100);
        printBinaryTreeArray(a,heapsize);
        heapsize=insert(a,heapsize,10);
        printBinaryTreeArray(a,heapsize);
        heapsize=insert(a,heapsize,113);
        printBinaryTreeArray(a,heapsize);
        heapsize=insert(a,heapsize,1);
        printBinaryTreeArray(a,heapsize);
        heapsize=insert(a,heapsize,-1);
        printBinaryTreeArray(a,heapsize);
        printImpData("Deleting entire tree, one min node at a time");
        while(heapsize!=0)
        {
            cout<<endl<<"Deleting min node "<<*a;
            heapsize=deleteMin(a,heapsize);
            printBinaryTreeArray(a,heapsize);
        }
        delete[] a;
    }
}
