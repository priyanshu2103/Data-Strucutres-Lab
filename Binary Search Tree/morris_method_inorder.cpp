#include <iostream>
#include <stdlib.h>
using namespace std;

typedef struct _node{
	struct _node* right;
	int data;
	struct _node* left;
}node;

node* createNode(int x)
{
	node* p=(node*)malloc(sizeof(struct _node));
	p->data=x;
	p->left=NULL;
	p->right=NULL;
	return p;
}

node* search(int x,node* p)
{
	if(p->data==x)
		return p;
	if(p->left!=NULL)
		if(search(x,p->left)!=NULL)
			return search(x,p->left);
	if(p->right!=NULL)
		if(search(x,p->right)!=NULL)
			return search(x,p->right);

	return NULL;
}

void setRight(node* p,node* q)
{
	if(p->right==NULL)
		p->right=q;
	else
		cout<<"Element already present"<<endl;
}

void setLeft(node* p,node* q)
{
	if(p->left==NULL)
		p->left=q;
	else
		cout<<"Element already present"<<endl;
}		

void morrisMethod(node* p)
{
	
	while(p!=NULL)
	{	
		if(p->left==NULL)
		{
			cout<<p->data<<endl;
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
				cout<<p->data<<endl;
				temp->right=NULL;
				p=p->right;
			}
		}
	}

}




int main()
{
	cout<<"Enter the number of elements you wanna insert"<<endl;
	int n;
	cin>>n;

	cout<<"enter root node"<<endl;
	int r;
	cin>>r;
	node* root=createNode(r);

	for(int i=0;i<n-1;i++)
	{
		int a,b;
		char c;
		cin>>a>>b>>c;

		if(c=='R'||c=='r')
		{
			node* p=search(a,root);
			node* q=createNode(b);
			setRight(p,q);
		}
		else
		{
			node* p=search(a,root);
			node* q=createNode(b);
			setLeft(p,q);
		}
	}

	morrisMethod(root);


}