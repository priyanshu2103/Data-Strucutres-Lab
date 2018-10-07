#include <iostream>
#include <stdlib.h>
using namespace std;

typedef struct _node
{
	int data;
	struct _node* left;
	struct _node* right;
	struct _node* parent;
}node;

node* createNode(int x)
{
	node* p=(node*)malloc(sizeof(struct _node));
	p->data=x;
	p->right=NULL;
	p->left=NULL;
	p->parent=NULL;
	return p;
}

node* BST_insert(node* p,int x)
{
	node* l=p;
	node* y=NULL;

	if(p==NULL)
		{p=createNode(x);return p;}
	else
	{
		while(l!=NULL)
		{
			y=l;		
			if(x>l->data)
				l=l->right;
			else
				l=l->left;
		}

		node* z=createNode(x);

		if(x>y->data)
		{	
			y->right=z;
			z->parent=y;
		}
		else
		{
			y->left=z;
			z->parent=y;
		}
		return p;
	}
}

void setRight(node* p,node* q)
{
	if(p->right==NULL)
	{
		p->right=q;
		q->parent=p;
	}
	else
	{
		cout<<"Element already exists";
	}
}

void setLeft(node* p,node* q)
{
	if(p->left==NULL)
	{
		p->left=q;
		q->parent=p;
	}
	else
	{
		cout<<"Element already exists";
	}
}

node* BST_min_diff(node* p)
{
	node* x=p;
	while(x->left!=NULL)
		x=x->left;
	return x;
}

node* BST_nonrecur(node* p,int x)
{
	while(p!=NULL)
	{
		if(p->data==x)
			return p;
		else if(x>p->data)
			p=p->right;
		else
			p=p->left;
	}
	return NULL;
}

node* BST_recur(node* p,int x)
{
	if(p!=NULL)
	{
		if(p->data==x)
			return p;
		else if(x>p->data)
			return BST_recur(p->right,x);
		else
			return BST_recur(p->left,x);
	}
	return NULL;
}

node* BST_successor(node* p)
{
	node* x=p;
	if(x->right!=NULL)
		return BST_min_diff(x->right);
	else
	{
		node* y=x->parent;
		if(y==NULL)
			return NULL;
		else
		{
			while(y!=NULL&&x==y->right)
			{
				x=y;
				y=y->parent;
			}
			return y;
		}
	}
}

int main()
{
	int n;
	cin>>n;
	node* root=NULL;

	int arr[n];
	for(int i=0;i<n;i++)
		cin>>arr[i];

	for(int i=0;i<n;i++)
	{
		root=BST_insert(root,arr[i]);
	}

	for(int i=0;i<n;i++)
	{
		node* p=BST_recur(root,arr[i]);
		node* suc=BST_successor(p);
		cout<<suc->data<<" ";
	}

}


