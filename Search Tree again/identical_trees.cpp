#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

typedef struct _node
{
	int data;
	struct _node* left;
	struct _node* right;
}node;

node* newNode(int x)
{
	node* p=(node*)malloc(sizeof(struct _node));
	p->data=x;
	p->right=NULL;
	p->left=NULL;
	return p;
}

bool identical_trees(node* p,node* q)
{
	if(p==NULL&&q==NULL)
		return true;
	if(p!=NULL&&q!=NULL)
	{
		if(p->data==q->data&&identical_trees(p->left,q->left)&&identical_trees(p->right,q->right))
			return true;
	}
	return false;
}

int main()
{
	node *root1 = newNode(1);
    node *root2 = newNode(1);

    root1->left = newNode(2);
    root1->right = newNode(3);
    root1->left->left  = newNode(4);
    root1->left->right = newNode(5); 
 
    root2->left = newNode(2);
    root2->right = newNode(3);
    root2->left->left = newNode(4);
    root2->left->right = newNode(5); 

    if(identical_trees(root1,root2))
    	cout<<"Identical trees";
    else
    	cout<<"Unidentical trees";
 
}