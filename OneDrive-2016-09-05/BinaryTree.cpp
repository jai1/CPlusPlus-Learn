#include<iostream>
using namespace std;

struct node
{
  float value;
  node *left;
  node *right;
};

class btree
{
    node *search(float , node *);
    void insert(float , node *);
    void destroy(node *);
    public:
    void search(float );
    void insert(float );
    void destroy();
    node *root;
    btree();
    ~btree();

};

btree::btree()
{
    root=NULL;
}

btree::~btree()
{
    destroy();
}

void btree::destroy()
{
    destroy(root);
}

void btree::destroy(node *i_leaf)
{
    if (i_leaf!=NULL)
    {
        destroy(i_leaf->left);
        destroy(i_leaf->right);
        delete i_leaf;
    }
}

void btree::insert(float i_value)
{
    if(root!=NULL)
    {
        insert( i_value,root);
    }
    else
    {
        root=new node;
        root->value=i_value;
        root->left=NULL;
        root->right=NULL;
    }
}

void btree::insert(float i_value,node *i_leaf)
{
    if(i_value<i_leaf->value)
    {
        if(i_leaf->left!=NULL)
        {
            insert(i_value,i_leaf->left);
        }
        else
        {
            i_leaf->left=new node;
            i_leaf->left->value=i_value;
            i_leaf->left->left=NULL;
            i_leaf->left->right=NULL;
        }
    }
    else
    {
        if(i_leaf->right!=NULL)
        {
            insert(i_value,i_leaf->right);
        }
        else
        {
            i_leaf->right=new node;
            i_leaf->right->value=i_value;
            i_leaf->right->left=NULL;
            i_leaf->right->right=NULL;
        }
    }
}

void btree::search(float i_value)
{
    node *temp=search(i_value,root);
    if(temp==NULL)
    {
        cout<<"\n=======================================";
        cout<<"\nThe Element "<<i_value<<" NOT found!!!";
        cout<<"\n=======================================";
    }
    else
    {
            cout<<"\n================================";
            cout<<"\nThe Element "<<i_value<<" found!!!";
            //cout<<"\nTo the left is"<<temp->left->value;
            //cout<<"\nTo the right is"<<temp->right->value;
            //cout<<"\n================================";
    }

}

node *btree::search(float i_value, node *i_leaf)
{
    if(i_leaf!=NULL)
    {
        if(i_leaf->value==i_value)
        {
            return i_leaf;
        }
        if(i_value<i_leaf->left->value)
        {
            return search(i_value,i_leaf->left);
        }
        else
        {
            return search(i_value,i_leaf->right);
        }
    }
    else
    {
        return NULL;
    }
}

int main()
{
    btree oBtree;
    oBtree.insert(1);
    oBtree.insert(10);
    oBtree.insert(6);
    oBtree.insert(14);
    oBtree.insert(5);
    oBtree.insert(8);
    oBtree.insert(22);
    oBtree.insert(11);
    oBtree.insert(18);
    oBtree.search(10);
    return 0;

}

