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

node* build_tree(int in[],int pre[],int start,int end,int* counter)
{
	if(start>end)
		return NULL;

	node* theNode=createNode(pre[(*counter)++]);

	if(start==end)
		return theNode;

	int index=search(in,start,end,theNode->data);

	theNode->left=build_tree(in,pre,start,index-1,counter);
	theNode->right=build_tree(in,pre,index+1,end,counter);
	
	return theNode;
}

void printTree(node* root)
{
	if(root!=NULL)
	{
		printTree(root->left);
		printTree(root->right);
		cout<<root->data<<" ";
	}
}

int main()
{
	cout<<"Tell the number of elements"<<endl;
	int n;
	cin>>n;

	int in[n],pre[n];

	for(int i=0;i<n;i++)
		cin>>in[i];

	for(int i=0;i<n;i++)
		cin>>pre[i];

	node* root=NULL;
	int counter=0;
	root=build_tree(in,pre,0,n-1,&counter);

	printTree(root);


}