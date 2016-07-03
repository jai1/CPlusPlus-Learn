#include <iostream>
#include <binaryTrees.h>
#include <limits>
#include<BST.h>
using namespace std;

/*
    A Tree with atmost two Children.
    Types of binary tree:-
    a. Strict/proper binary tree
        Each node is either a leaf node or has 2 children i.e
        there is no node with one child only.
    b. Complete Binary Tree:-
        - All levels except the last are completely filled and
          all nodes are as left as possible.
        - The Height of this tree is minimum.
        - Considering the root as level 0.
        - Max no of nodes at each level is (2^i)
          where i is the level (depth) of the node
        - Height of a complete binary tree is:-
            floor (log (no of nodes)) - [Base is 2]
    c. Perfect Binary tree:-
        - All levels are completely filled
        - Max no of nodes = (2^height of tree) - 1
        - Height of the tree is
            h = log(n + 1) - 1 - [Base is 2]
    d. Balanced binary tree:-
        Difference between height of left and  right subtree
        for every node is not more than k, where k is 1 in most
        cases.
        diff = | h(left subtree) - h(right subtree)|

    Note:-  To increase efficiency and reduce operation cost
            keep the height as minimum. Hence the tree must be
            atleast balanced, a perfect binary tree is desirable.
*/

/*
    Binary trees can be implemented using.
    a. Linked lists
    b. Arrays -> Perfect/Complete binary tree
                 Root is  0th index
                 Node at index i
                 left child index = 2i + 1
                 right child index = 2i + 2
              -> Used for heap
*/

/* Template:-
    struct Node {
        int data;
        Node* left;
        Node* right;
    };
*/


namespace BT
{
    /*
        returns numeric_limits<int>::min() if node is NULL
        else compares it's values with the value of it's sub nodes
        Note:- max and min functions take only 2 arguments
        If root itself is NULL than numeric_limits<int>::min() is
        returned.
    */

    int findMax(BTNode *node)
    {
        if (node==NULL)
            return numeric_limits<int>::min();
        else
            return max(node->value,
                max(findMax(node->right),findMax(node->left)));
    }
    /*
        returns numeric_limits<int>::max() if node is NULL
        else compares it's values with the value of it's sub nodes
        Note:- max and min functions take only 2 arguments
        If root itself is NULL than numeric_limits<int>::max() is
        returned.
    */
    int findMin(BTNode *node)
    {
        if (node==NULL)
            return numeric_limits<int>::max();
        else
            return min(node->value,
                min(findMin(node->right),findMin(node->left)));
    }

    // Returns the given node but with value added to the tree.
    BTNode* insert(BTNode* node, int i_value)
    {
        if(node == NULL)
        {
            node=new BTNode(i_value);
            return node;
        }

        /* generate secret number between 1 and 10: */
        int dir = rand() % 2 + 1;
        if(dir == 1)
        {
            node->left = insert(node->left,i_value);
        }
        else
        {
            node->right = insert(node->right,i_value);
        }
        return node;
    }

    void printTopView(BTNode *root)
    {
        BTNode *node;
        if (root == NULL)
        {
            printError("Root itself is NULL");
            return;
        }
        std::queue<BTNode*> my_queue;
        my_queue.push(root);
        int level=0,temp=1;
        cout<<endl;
        while (my_queue.size()!=0)
        {
            if(temp%int(pow(2,level)) == 0)
            {
                cout<<endl;
                level++;
            }
            temp++;
            node=my_queue.front();
            my_queue.pop();
            if (node==NULL)
            {
                cout<<"NULL\t";
                continue;
            }
            cout<<node->value<<"\t";
            my_queue.push(node->left);
            my_queue.push(node->right);
        }
    }

        //Hence also called level order
    /*
        If tree is not a binary tree then we can use this algo:-
        Time Complexity - O(n)
        Space Complexity - (b^m) where m is the max depth
                            b is the max branching factor
        Can't maintain path in BFS need separate variables for it.
    */
    bool breadthFirstSearch(BTNode* root, int i_value=0)
    {
        BTNode* node;
        std::queue<BTNode*> my_queue;
        my_queue.push(root);
        while (my_queue.size()!=0)
        {
            node=my_queue.front();
            my_queue.pop();
            if (node == NULL)
                continue;
            else if(node->value == i_value)
            {
                cout<<"\nThe node is found";
                return true;
            }
            cout<<"\nReached node "<<node->value;
            my_queue.push(node->left);
            my_queue.push(node->right);
        }
        cout<<"\nValue not found in tree";
        return false;
    }

    //All same as breadFirst except 2statements
    /*
        Types:
        <root><left><right> -> Preorder
            D   L       R
        <left><root><right> -> Inorder -> Used in compilers for calculator
            L   D       R
        <left><right><root> -> Postorder
            L   R       D
        Here we use Preorder hence we push the right side before the left.
    */
    /*
        Time Complexity is O(n)
        Space Complexity - (b*m)
            where b is the branching factor
            m is the max depth
    */
    bool depthFirstSearch(BTNode* root, int i_value=0)
    {
        BTNode* node;
        std::deque<BTNode*> my_queue;
        my_queue.push_back(root);
        while (my_queue.size()!=0)
        {
            //Different lines
            node=my_queue.back();
            my_queue.pop_back();

            if (node == NULL)
                continue;
            else if(node->value == i_value)
            {
                cout<<"\nThe node is found";
                return true;
            }
            cout<<"\nReached node "<<node->value;
            my_queue.push_back(node->right);
            my_queue.push_back(node->left);
        }
        cout<<"\nValue not found in tree";
        return false;
    }

    void learn()
    {
        /* initialize random seed: */
        srand (time(0));
        // Note:- Never initialize the srand in the func you are using
        // it in else it will give the same value always.
        printHeader("Learning binaryTree");
        BTNode* root=NULL;
        root=insert(root,15);
        insert(root,10);
        insert(root,20);
        insert(root,25);
        insert(root,8);
        insert(root,12);
        insert(root,17);
        insert(root,170);
        BT::printTopView(root);
        char pre[100]={0};
        sprintf(pre,"Result of breadthFirstSearch for value 17 is %d",
                breadthFirstSearch(root,17));
        printImpData(pre);
        sprintf(pre,"Result of depthFirstSearch for value 17 is %d",
                depthFirstSearch(root,17));
        sprintf(pre,"Max value in the tree is %d",findMax(root));
        printImpData(pre);
        sprintf(pre,"Min value in the tree is %d",findMin(root));
        printImpData(pre);
        sprintf(pre,"Is the formed tree a binary tree? %d" ,
                BST::isBinaryTree(root));
        printImpData(pre);
        delete root;
    }

}
