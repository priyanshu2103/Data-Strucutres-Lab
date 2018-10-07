#include <iostream>
#include <stdlib.h>
using namespace std;

typedef struct _node
{
	int data;
	struct _node* left;
	struct _node* right;
}node;

node* createNode(int x)
{
	node* p=(node*)malloc(sizeof(struct _node));
	p->data=x;
	p->right=NULL;
	p->left=NULL;
	return p;
}

int search(int in[],int start,int end,int data)
{
	for(int i=start;i<=end;i++)
	{
		if(in[i]==data)
			return i;
	}
}

node* build_tree(int in[],int post[],int start,int end,int* counter)
{
	if(start>end)
		return NULL;

	node* theNode=createNode(post[(*counter)--]);
	if(start==end)
		return theNode;

	int index=search(in,start,end,theNode->data);

	theNode->right=build_tree(in,post,index+1,end,counter);
	theNode->left=build_tree(in,post,start,index-1,counter);

	return theNode;
}

void printTree(node* p)
{
	if(p!=NULL)
	{
		cout<<p->data<<" ";
		printTree(p->left);
		printTree(p->right);
	}
}

int main()
{
	cout<<"Tell the number of elements";
	int n;
	cin>>n;
	int in[n],post[n];

	for(int i=0;i<n;i++)
		cin>>in[i];
	for(int i=0;i<n;i++)
		cin>>post[i];

	int counter=n-1;
	node* root=NULL;

	root=build_tree(in,post,0,n-1,&counter);

	printTree(root);
}