#include <iostream>
#include <stdlib.h>
using namespace std;

typedef struct _node
{
	int data;
	struct _node* left;
	struct _node* right;
	bool rightThread;
}node;

node* createNode(int x)
{
	node* p=(node*)malloc(sizeof(struct _node));
	p->data=x;
	p->right=NULL;
	p->left=NULL;
	p->rightThread=false;
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
	if(p->right!=NULL&&p->rightThread==false){
		if(search(x,p->right)!=NULL&&p->rightThread==false)
			return search(x,p->right);
	}
	return NULL;                                                                                                                
}

void setleft(node* p,node* q)
{
	if(p->left==NULL){
		p->left=q;
		p->right=q;
		p->rightThread=true;
	}
	else{
		cout<<"Element already exists"<<endl;
		exit(1);
	}
}

void setRight(node* p,node* q)
{
	if(p->right==NULL||p->rightThread==true){
		q->right=p->right;
		p->right=q;
		p->rightThread=false;
		q->rightThread=true;
	}
	else{
		cout<<"Element already exists"<<endl;
		exit(1);
	}
	
}

void postorder(node* p){

}

void inorder(node* p)
{
	node* q;                                              // this q NULL can't be defined inside as this will stop the code in the end, if node* q is not defined inside
	do{														// code will not stop
		q=NULL;
		while(p!=NULL){ 
			q=p;
			p=p->left;
		}
		if(q!=NULL){
			cout<<q->data<<endl;    	
			p=q;
			p=p->right;
			while(q->rightThread==true&&p!=NULL){
				cout<<p->data<<endl;
				q=p;
				p=p->right;
			}
		}
	}while(q!=NULL);
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
	
}