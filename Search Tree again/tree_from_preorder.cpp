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

node* build_tree(int pre[],int start,int end,int n,int* counter)
{
	if(start>end)
		return NULL;

	node* theNode=createNode(pre[(*counter)++]);

	if(start==end)
		return theNode;
	int i;
	for(i=start;i<=end;i++)
		if(pre[i]>theNode->data)
			break;

	theNode->left=build_tree(pre,*counter,i-1,n,counter);
	theNode->right=build_tree(pre,i,end,n,counter);

	return theNode;
}

void setRight(node* p,node* q)
{
	if(p->right==NULL)
		p->right=q;
	else
		cout<<"Element already exists";
}

void morrisMethod(node* root)
{
	node* p=root;
	while(p!=NULL)
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

void morrisPreorder(node* root)
{
	
}

int main()
{
	int n;
	cin>>n;
	int pre[n];

	node* root=NULL;

	for(int i=0;i<n;i++)
		cin>>pre[i];

	int counter=0;
	root=build_tree(pre,0,n-1,n,&counter);

	morrisPreorder(root);
}