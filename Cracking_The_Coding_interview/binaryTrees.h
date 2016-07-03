#include <peripherals.h>
#include <string.h>
#include <queue>
#include <math.h>
#include <stdio.h>
#include <deque>
#include <time.h>
#include <stdlib.h>
#ifndef BINARYTREES_H_INCLUDED
#define BINARYTREES_H_INCLUDED
struct BTNode
{
    int value;
    BTNode *left, *right;
    BTNode(int i_value=0)
    {
        left=right=NULL;
        value=i_value;
    }
    ~BTNode()
    {
        if (left != NULL)
            delete left;
        if(right != NULL)
            delete right;
    }
};


namespace BT{
void learn();
void printTopView(BTNode *root);
int findMin(BTNode *node);
int findMax(BTNode *node);
}
#endif // BINARYTREES_H_INCLUDED
