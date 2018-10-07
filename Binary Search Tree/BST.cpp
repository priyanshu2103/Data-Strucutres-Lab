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
		{
			p=createNode(x);
			return p;
		}
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


void morrisMethod(node* root)
{
	node* p=root;
	while(p!=NULL)
	{
		if(p->left==NULL)
		{
			cout<<p->data<<" ";
			p=p->right;
		}
		else
		{
			node* temp=p->left;
			while(temp->right!=NULL&&temp->right!=p)
				temp=temp->right;

			if(temp->right==NULL)
			{
				setRight(temp,p);
				p=p->left;
			}
			else
			{
				cout<<p->data<<" ";
				temp->right=NULL;
				p=p->right;
			}
		}
	
	}
}

void inorder(node* p)
{
	if(p!=NULL)
	{
		inorder(p->left);
		cout<<p->data<<" ";
		inorder(p->right);
	}
}

int BST_min(node* p)
{
	node* x=p;
	while(x->left!=NULL)
		x=x->left;
	return x->data;
}

int BST_max(node* p)
{
	node* x=p;
	while(x->right!=NULL)
		x=x->right;
	return x->data;
}

node* BST_min_diff(node* p)
{
	node* x=p;
	while(x->left!=NULL)
		x=x->left;
	return x;
}


int main()
{
	int n;
	cin>>n;
	node* root=NULL;

	for(int i=0;i<n;i++)
	{
		int a;
		cin>>a;
		root=BST_insert(root,a);
	}

	cout<<endl;
	morrisMethod(root);
	cout<<endl;
	inorder(root);
	cout<<endl;

	int min;
	min=BST_min(root);
	cout<<"The minimum element in this tree is: "<<min<<endl;

	int max;
	max=BST_max(root);
	cout<<"The maximum element in this tree is: "<<max<<endl;

}
