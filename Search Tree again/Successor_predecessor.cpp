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


int successor(node* root,int x)
{
	node* p=BST_nonrecur(root,x);
	if(p->right!=NULL)
	{
		return BST_min(p->right);
	}

	else if(p->data==BST_max(root)) return -1;
	else 
	{
		node* temp=(node*)malloc(sizeof(struct _node));
		temp=p->parent;
		while(temp!=NULL&&p==temp->right)
		{
			p=temp;
			temp=p->parent;
		}
		return temp->data;
	}
}

int predecessor(node* root, int x)
{
	node* p=BST_nonrecur(root,x);

	if(p->left!=NULL)
		return BST_max(p->right);

	else if(p->data==BST_min(root))
		return -1;
	else
	{
		node* temp=p->parent;
		while(temp!=NULL&&p==temp->left)
		{
			p=temp;
			temp=temp->parent;
		}
		return temp->data;
	}

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

		int a=predecessor(root,20);
		if(a==-1) 
			cout<<"Does not exists";
		cout<<a<<endl;
	

}


