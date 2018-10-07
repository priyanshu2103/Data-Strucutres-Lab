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

void setRight(node* p,node* q)
{
	if(p->right==NULL)
		p->right=q;
	else
		cout<<"Elemet exists";
}

void setLeft(node* p,node* q)
{
	if(p->left==NULL)
		p->left=q;
	else
		cout<<"Elemet exists";
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
		node* temp=p->parent;
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

void MorrisPreorder(node * root)
{
	if(root==NULL) return;

	node * p = root;

	while(p!=NULL)
	{
		if(p->left==NULL)
		{
			cout<<p->data<<" ";
			p=p->right;
		}
		else
		{
			node * pred = p->left;

			while(pred->right!=NULL && pred->right!=p)
				pred=pred->right;

			if(pred->right==NULL)
			{
				cout<<p->data<<" ";
				pred->right=p;
				p=p->left;
			}
			else
			{
				pred->right=NULL;
				p=p->right;
			}
		}
	}
}


void delete_node(struct _node* root,int x)
{
	struct _node* p=BST_nonrecur(root,x);

	if(p==NULL)
	{
		cout<<"key not found"<<endl;
		return ;
	}

	else
	{
		if(p->left==NULL&&p->right==NULL)
		{	
			if(p->parent->left==p)
				p->parent->left=NULL;
			else 
				p->parent->right=NULL;
			return ;
		}
		else if(p->left!=NULL&&p->right==NULL)
		{
			p->data=p->left->data;
			p->left=NULL;
			free(p->left);
		}
		else if(p->left==NULL&&p->right!=NULL)
		{
			p->data=p->right->data;
			p->right=NULL;
			free(p->right);
		}
		else
		{
			int s=successor(root,x);//data to be copied at the node to be deleted
			node* temp=BST_nonrecur(root,s);//this node has to be deleted
			p->data=s;
			if(temp->left==NULL&&temp->right==NULL)
			{	
				if(temp->parent->left==temp)
					temp->parent->left=NULL;
				else 
					temp->parent->right=NULL;
				return ;
			}
			else if(temp->left!=NULL&&temp->right==NULL)
			{
				temp->data=temp->left->data;
				temp->left=NULL;
				free(temp->left);
			}
			else if(temp->left==NULL&&temp->right!=NULL)
			{
				temp->data=temp->right->data;
				temp->right=NULL;
				free(temp->right);
			}
		}
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
	morrisMethod(root);
	cout<<endl;
	
	int min;
	min=BST_min(root);
	cout<<"The minimum element in this tree is: "<<min<<endl;

	int max;
	max=BST_max(root);
	cout<<"The maximum element in this tree is: "<<max<<endl;

	MorrisPreorder(root);


}
