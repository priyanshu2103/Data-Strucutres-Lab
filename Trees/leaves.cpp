#include <iostream>
#include <stdlib.h>
using namespace std;

int count=0;

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

node* search(int x,node* q)                     // search function is in order transversal
{	
	if(q->data==x) 
		return q;
	if(q->left!=NULL)
		if(search(x,q->left)!=NULL)
			return search(x,q->left);
	if(q->right!=NULL)
		if(search(x,q->right)!=NULL)
			return search(x,q->right);
	return NULL;                                                                    
}

void setleft(node* p,node* q)
{                                                                                      
	if(p->left==NULL) p->left=q;
	else {
		cout<<"Element already exists"<<endl;
		exit(1);
	}
}

void setRight(node* p,node* q)
{
	if(p->right==NULL) p->right=q;
	else {
		cout<<"Element already exists"<<endl;
		exit(2);
	}
}

void inorder(node* p){
	if(p!=NULL){
		inorder(p->left);
		if(p->left==NULL&&p->right==NULL) count++;
		inorder(p->right);
	}
}


int main()
{
	cout<<"Number of elements"<<endl;
	int num;
	cin>>num;

	node* root=NULL;
	cout<<"Enter root element"<<endl;
	int r;
	cin>>r;
	root=createNode(r);

	cout<<"Enter the elements in num1,num2,L/R format"<<endl;
	
	for(int i=0;i<num-1;i++)
	{
		int a,b;
		cin>>a>>b;
		char c;
		cin>>c;
		if(c=='R'||c=='r'){
			node* p=search(a,root);
			node* q=createNode(b);
			setRight(p,q);
		}
		else{
			node* p=search(a,root);
			node* q=createNode(b);
			setleft(p,q);
		}
	}

	inorder(root);
	cout<<count;

}