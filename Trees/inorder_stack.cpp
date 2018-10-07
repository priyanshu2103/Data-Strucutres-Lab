#include <iostream>
#include <stdlib.h>
using namespace std;

typedef struct _node
{
	int data;
	struct _node* left;
	struct _node* right;
}node;

typedef struct _stack
{
	struct _stack* next;
	struct _node* data;
}stack1;

node* createNode(int x)
{
	node* p=(node*)malloc(sizeof(struct _node));
	p->data=x;
	p->right=NULL;
	p->left=NULL;
	return p;
}

node* search(int x,node* p)
{
	if(p->data==x)
		return p;
	if(p->left!=NULL){
		if(search(x,p->left)!=NULL)
			return search(x,p->left);
	}
	if(p->right!=NULL){
		if(search(x,p->right)!=NULL)
			return search(x,p->right);
	}
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

stack1* push(stack1* top,node* x){
	stack1* temp=(stack1*)malloc(sizeof(struct _stack));
	temp->data=x;
	temp->next=NULL;
	if(top==NULL){
		top=temp;
		return top;
	}
	else{
		temp->next=top;
		top=temp;
		return top;
	}
}

node* pop(stack1** top){
	if(*top!=NULL){
		node* new1=(node*)malloc(sizeof(struct _node));
		new1=(*top)->data;

		stack1* temp=(stack1*)malloc(sizeof(struct _stack));
		temp=*top;
		*top=(*top)->next;
		free(temp);
		return new1;
	}
	else return NULL;
}

void inorder(node* p,stack1* top){
	while(top!=NULL|| p!=NULL){
		while(p!=NULL){
			top=push(top,p);
			p=p->left;
		}
		if(top!=NULL){
			p=pop(&top);
			cout<<p->data<<endl;
			p=p->right;
		}
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
	stack1* top=(stack1*)malloc(sizeof(struct _stack));
	top=NULL;
	inorder(root,top);
}