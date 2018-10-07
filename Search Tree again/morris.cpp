#include<bits/stdc++.h>
using namespace std;


struct _tree
{
	int data;
	struct _tree* left;
	struct _tree* right;
}Node;

struct _tree* newnode(int x)
{
	struct _tree* temp=(struct _tree*)malloc(sizeof(struct _tree));
	temp->data=x;
	temp->left=NULL;
	temp->right=NULL;
	return temp;	
}

void set_right(struct _tree* p,struct _tree* q)
{	
	if(p!=NULL)
	{
		p->right=q;
	}
}

void set_left(struct _tree* p,struct _tree* q)
{	
	if(p!=NULL)
	{
		p->left=q;
	}
}

struct _tree* search(int key,struct _tree* p)
{
	if(p->data==key)
	{
		return p;
	}
	 if(p->left!=NULL)
	{
		if(search(key,p->left)!=NULL){return search(key,p->left);}
	}
	 if(p->right!=NULL)
	{
		if(search(key,p->right)!=NULL){return search(key,p->right);}
	}
	return NULL;
}

void inorder_using_morris(struct _tree* root)
{
	struct _tree* p=root;
	struct _tree* temp;
	while(p!=NULL)
	{
		if(p->left==NULL)
		{
			cout<<p->data<<" ";p=p->right;
		}
		else 
		{
			temp=p->left;
			while(temp->right!=NULL&&temp->right!=p)
			{
				temp=temp->right;
			}
			if(temp->right==NULL)
			{
				set_right(temp,p);
				p=p->left;
			}
			else
			{
				cout<<p->data<<" ";temp->right=NULL;p=p->right;
			}
		}
	}
}

//for inorder to preorder just change the cout from else to if and it will work

void preorder_using_morris(struct _tree* root)
{
	struct _tree* p=root;
	struct _tree* temp;
	while(p!=NULL)
	{
		if(p->left==NULL)
		{
			cout<<p->data<<" ";p=p->right;
		}
		else 
		{
			temp=p->left;
			while(temp->right!=NULL&&temp->right!=p)
			{
				temp=temp->right;
			}
			if(temp->right==NULL)
			{
				cout<<p->data<<" ";set_right(temp,p);p=p->left; 
			}
			else 
			{
				temp->right=NULL;p=p->right;
			}
		}
	}
}


//This is Post Order :children before node( L ,R , N)
void morrisPostorderTraversal(struct _tree* root)
{

// Making our tree left subtree of a dummy Node
struct _tree* dummyRoot = newnode(0);
dummyRoot->left = root;

//Think of P as the current node 
struct _tree* p = dummyRoot, *pred, *first, *middle, *last;
while(p!=NULL){        

    if(p->left == NULL){
        p = p->right;
    } else{
        /* p has a left child => it also has a predeccessor
           make p as right child predeccessor of p    
        */
        pred = p->left;
        while(pred->right!=NULL && pred->right != p){
            pred = pred->right;
        }

        if(pred->right == NULL){ 

            // predeccessor found for first time
            // modify the tree

            pred->right = p;    
            p = p->left;

        }else {                          

           // predeccessor found second time
           // reverse the right references in chain from pred to p
            first = p;
            middle = p->left;              
            while(middle!=p){            
                last = middle->right;
                middle->right = first;
                first = middle;
                middle = last;
            }

            // visit the nodes from pred to p
            // again reverse the right references from pred to p    
            first = p;
            middle = pred;
            while(middle!=p){

                cout<<" "<<middle->data;  
                last = middle->right;          
                middle->right = first;
                first = middle;
                middle = last;
            }

            // remove the pred to node reference to restore the tree structure
            pred->right = NULL;    
            p = p-> right;
        }
    }
}    
}
int main()
{
	int num;
        cin>>num;
        int z,a,num1,num2;
        char c;
        cin>>z>>a>>c;
        //cin>>c;
        struct _tree* root=newnode(z);
        for(int i=0;i<num-1;i++)
        {
                cin>>num1>>num2>>c;
                //cin>>c;
                if(num2==-1){cout<<z<<"already present at specified positon of"<<num1<<endl;continue;}
                if(num2!=-1)
                {
                        if(c=='L')
                        {
                                struct _tree* p=search(num2,root);
                                //cout<<p->data<<endl;

                                if(p->left!=NULL)
                                {
                                        cout<<p->left->data <<"already present at specified positon of "<<num1<<endl;
                                }
                                else
                                {
                                        struct _tree* q=newnode(num1);
                                        //cout<<q->data<<"child data"<<endl;
                                        set_left(p,q);
                                }
                        }
                        else if(c=='R')
                        {
                                struct _tree* p=search(num2,root);
                                //cout<<p->data<<endl;
                                if(p->right!=NULL)
                                {
                                        cout<<p->right->data <<"already present at specified positon of "<<num1<<endl;
                                }
                                else
                                {
                                        struct _tree* q=newnode(num1);
                                        //cout<<q->data<<"child data"<<endl;
                                        set_right(p,q);
                                }
                        }
                }
        }
        cout<<endl;
        inorder_using_morris(root);
        cout<<endl;
        preorder_using_morris(root);
        cout<<endl;
        morrisPostorderTraversal(root);
}