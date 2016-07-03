#include<iostream>
#include <binaryTrees.h>
using namespace std;
/*
    Binary Search Tree (BST) is a data structure in which all the
    values in left subtree is lesser or equal than the value
    of the node and all the values in the right subtree
    is greater than the value of the node.

    Invariant:-
    - Assume that the lesser than or equal value is stored in the left
      side of the tree and greater that value is stored in the right side
      of the tree.
      Hence for every node the
        node value >= max(left subtree)
        node value <  min(right subtree)

    For balanced tree:-
    Search - O(log n) - [Base 2]
    Insert - O(log n) - [Base 2]
    Remove - O(log n) - [Base 2]
*/

/*
    queue:-
    front                   back
    ----------------------
    <- Pop                  <- Push
    ----------------------

    deque:-
    front                   back
    ----------------------
    <- Pop                  <- Push
    -> push_front           -> pop_back
    ----------------------

*/
namespace BST
{
    // Returns true if the given tree is a binary tree
    bool isBinaryTree(BTNode* node)
    {
        //since an empty tree is also a binary tree
        if (node == NULL)
            return true;
        return ( node->value >= BT::findMax(node->left) &&
            isBinaryTree(node->left) &&
            node->value < BT::findMin(node->right) &&
            isBinaryTree(node->right));
    }



    // Prints whether the given i_value is to the left or right of the node
    // Termination condition:-
    //          i_value is found in the Tree
    //          left and right nodes are empty
    // In case of duplicate values, the recursion continues till node != thisNode

    void pathFromNode(BTNode* node, char *pre, int i_value=0,BTNode* thisNode=NULL)
    {
        if (node == NULL)
        {
           cout<<"\n"<<pre<<"The node is NULL i.e value Not Found";
           return;
        }
        if (thisNode!=NULL )
        {
            i_value=thisNode->value;
            if(thisNode == node)
            {
                cout<<"\n"<<pre<<"Value found at memory address "<<node;
                delete pre;
                return;
            }
        }
        else if (node->value == i_value)
        {
            cout<<"\n"<<pre<<"Value found at memory address "<<node;
            return;
        }
        if (i_value <= node->value)
        {
            cout<<"\n"<<pre<<"Checking left subtree "<<node->value;
            pre=strcat(pre,"\t");
            pathFromNode(node->left,pre,i_value,thisNode);
        }
        else
        {
            cout<<"\n"<<pre<<"Checking right subtree "<<node->value;
            pre=strcat(pre,"\t");
            pathFromNode(node->right,pre,i_value,thisNode);
        }
    }

    // The function returns the memory address of the node where the value is
    // inserted.
    // Returns the given node but with value added to the tree.
    BTNode * insert(BTNode* node, int i_value)
    {
        //Base case or Halting Measure
        if(node==NULL)
        {
            node=new BTNode(i_value);
            printImpData("Inserted a new node:-");
        }
        else if (i_value <= node->value)
        {
            node->left=insert(node->left,i_value);
        }
        else
        {
            node->right=insert(node->right,i_value);
        }
        return node;
    }

    // Min is the leftmost node.
    // If a node has no left node then it is the min node.
    int findMin(BTNode* root)
    {
        if(root==NULL)
        {
            printError("The root is NULL, hence retuning -1");
            return -1;
        }
        int minValue=root->value;
        BTNode* node=root->left;
        while(node!=NULL)
        {
            minValue=node->value;
            node=node->left;
        }
        return minValue;
    }

    // Max is the rightmost node.
    // If a node has no right node then it is the max node.
    int findMax(BTNode* root)
    {
        if(root==NULL)
        {
            printError("The root is NULL, hence retuning -1");
            return -1;
        }
        int maxValue=root->value;
        BTNode* node=root->right;
        while(node!=NULL)
        {
            maxValue=node->value;
            node=node->right;
        }
        return maxValue;
    }
    //Height of the Tree:-
    //  No of edges in longest path from root to a leaf node.
    //  Height = Max Depth
    // Recursion:- At each node
    //   height == max(left subtree Height,right subtree Height) + 1
    int findHeight(BTNode* node, int currentHeight=0)
    {
        // Termination condition
        if(node==NULL)
            return currentHeight;
        int leftHeight=findHeight(node->left,currentHeight+1);
        int rightHeight=findHeight(node->right,currentHeight+1);
        return max(leftHeight,rightHeight) ;
    }

    BTNode* searchNode(BTNode* node, int i_value)
    {
        if(node == NULL)
        {
            cout<<"\nNot Found";
            return NULL;
        }
        else if (node->value == i_value)
            return node;
        else if (i_value <= node->value)
            return searchNode(node->left,i_value);
        else
            return searchNode(node->right,i_value);
    }

/*
    Property of a binary tree is that for every node:-
    - min(right subtree) > value >= max(left subtree)
    - for a min(tree) is left most node
    - for a max(tree) is right most node

    Deletion of a node from a binary tree.
    - Since the tree is a binary tree every deleted node can be replaced by either:-
    a. max(left subtree)
    b. min(right subtree)
*/
    BTNode* findAndDeleteNode(BTNode* node, int i_value)
    {
        //First Finding
        if(node==NULL)  return NULL;
        else if(i_value < node->value) node->left = findAndDeleteNode(node->left,i_value);
        else if (i_value > node->value) node->right = findAndDeleteNode(node->right,i_value);
        else // value found
        {
            //Case 1 -> Node has no child trees
            if(node->left==NULL && node->right==NULL)
            {
                delete node;
                return NULL;
            }
            //Case 2 -> Left child only
            else if(node->left == NULL)
            {
                BTNode* temp=node;
                node = node->right;
                delete temp;
                return node;
            }
            //Case 3 -> Right child only
            else if(node->right == NULL)
            {
                BTNode* temp=node;
                node = node->left;
                delete temp;
                return node;
            }
            //Case 4-> Node has both child
            else
            {
                node->value=findMin(node->right);
                // since Min node has no left child this function will be caught
                // by case 2and deleted there.
                node->right=findAndDeleteNode(node->right, node->value);
                return node;
            }

        }

    }

    void printLikeArray(BTNode* node)
    {
        if(node == NULL)
            return;
        printLikeArray(node->left);
        cout<<node->value<<" ";
        printLikeArray(node->right);
    }
    void learn()
    {
        printHeader("Learning binarySearchTree");
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
        sprintf(pre,"MinValue of tree is %d",findMin(root));
        printImpData(pre);
        sprintf(pre,"MaxValue of tree is %d",findMax(root));
        printImpData(pre);
        sprintf(pre,"Height of tree is %d",findHeight(root));
        printImpData(pre);
        strncpy(pre,"\0",sizeof(pre));
        printImpData("Path to reach 12");
        pathFromNode(root,pre,170);
        printImpData(pre);
        sprintf(pre,"Is the formed tree a binary tree? %d" , isBinaryTree(root));
        printImpData(pre);
        printImpData("Testing isBinaryTree -> Interview question.");
        BTNode* t=insert(root,22);

        // Test searchNode
        printImpData("Finding value 20");
        t=searchNode(root, 20);
        printImpData("Finding value 21");
        t=searchNode(root, 21);

        // print sorted array
        printImpData("Printing like array");
        printLikeArray(root);

        // findAndDelete
        printImpData("Deleting value 20");
        root=findAndDeleteNode(root,20);
        BT::printTopView(root);
        printImpData("Deleting value 17");
        root=findAndDeleteNode(root,17);
        BT::printTopView(root);


        delete root;
    }
}
