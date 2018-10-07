//search ,insertion ,deletion ,sequence validity,inorder,height,successor,predecessor,minimum,maximum
//all in one
#include<bits/stdc++.h>
using namespace std;

struct _tree
{
	int data;
	struct _tree *left,*right,*parent;
};

struct _tree* newnode(int key)
{
	struct _tree* temp=(struct _tree*)malloc(sizeof(struct _tree));
	temp->data=key;
	temp->left=NULL;
	temp->right=NULL;
	temp->parent=NULL;
}

struct _tree* insert(struct _tree* root,int x)
{
	struct _tree* p=root;
	struct _tree* temp=NULL;
	if(p==NULL)
	{
		p=newnode(x);
		return p;
	}
	else 
	{
		while(p!=NULL)
		{
			temp=p;
			if(x>p->data)
			{
				p=p->right;
			}
			else if(x<p->data)
			{
				p=p->left;
			}
		}

		if(x>temp->data)
		{
			struct _tree* q=newnode(x);
			temp->right=q;
			q->parent=temp;
		}
		else if(x<temp->data)
		{
			struct _tree* q=newnode(x);
			temp->left=q;
			q->parent=temp;
		}
	}
}

void inorder(struct _tree* root)
{
	struct _tree* p=root;
	if(p!=NULL)
	{
		inorder(p->left);
		cout<<p->data<<" ";
		inorder(p->right);
	}
}

int height_of_tree(struct _tree* p)
{
	if(p==NULL)
	{
		return 0;
	}
	else 
	{
		int lheight=height_of_tree(p->left);
		int rheight=height_of_tree(p->right);

		if(lheight>rheight){return (lheight+1);}
		else return (rheight+1);
	}
}

struct _tree* search(struct _tree* root,int x)
{
	struct _tree* p=root;
	while(p!=NULL&&p->data!=x)
	{
		if(x<p->data){p=p->left;}
		else p=p->right;
	}
	return p;
}

int maximum(struct _tree* root)
{
	struct _tree* x=root;
	while(x->right!=NULL)
	{
		x=x->right;
	}
	return x->data;
}

int  minimum(struct _tree* root)
{
	struct _tree* x=root;
	while(x->left!=NULL)
	{
		x=x->left;
	}
	return x->data;
}

int sucessor(struct _tree* root,int x)
{
	struct _tree* p=search(root,x);
	if(p->right!=NULL)
	{
		return minimum(p->right);
	}
	else 
	{
		struct _tree* temp=p->parent;
		while(temp!=NULL&&p==temp->right)
		{
			p=temp;
			temp=p->parent;
		}
		return temp->data;
	}
}

int predecessor(struct _tree* root,int x)
{
	struct _tree* p=search(root,x);
	if(p->left!=NULL)
	{
		return maximum(p->left);
	}
	else
	{
		struct _tree* temp=p->parent;
		while(temp!=NULL&&p==temp->left)
		{
			p=temp;
			temp=p->parent;
		}
		return temp->data;
	}
}

void delete_node(struct _tree* root,int x)
{
	struct _tree* p=search(root,x);
	if(p==NULL){cout<<"key not found"<<endl;return ;}
	else
	{
		if(p->left==NULL&&p->right==NULL)
		{	
			if(p->parent->left==p){p->parent->left=NULL;}
			else p->parent->right=NULL;
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
			int s=sucessor(root,x);//data to be copied at the node to be deleted
			struct _tree* temp=search(root,s);//this node has to be deleted
			p->data=s;
			if(temp->left==NULL&&temp->right==NULL)
			{	
				if(temp->parent->left==temp){temp->parent->left=NULL;}
				else temp->parent->right=NULL;
				return ;
			}
			else if(temp->left!=NULL&&temp->right==NULL)
			{
				temp->data=p->left->data;
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

bool is_sequence_valid(int a[],int min,int max,int n,int key)
{
	for(int i=0;i<n;i++)
	{
		if(a[i]>max||a[i]<min)
		{
			return false;
		}
		if(a[i]<key)
		{
			min=a[i]+1;
		}
		if(a[i]>key)
		{
			max=a[i]-1;
		}
		
	}
	return true;
}

int main()
{
	struct _tree* root=NULL;
	root=insert(root,50);
	insert(root,30);
	insert(root,20);
	insert(root,40);
	insert(root,70);
	insert(root,60);
	insert(root,80);
	struct _tree* p=NULL;
	int key;
	cout<<"enter the key to be searched "<<endl;
	cin>>key;
	p=search(root,key);
	if(p!=NULL){cout<<p->data<<" is already present in tree"<<endl;}
	else 
	{
		insert(root,key);
		cout<<"key is not present in the tree hence added "<<endl;
	}
	inorder(root);
	cout<<endl;
	cout<<height_of_tree(root);
	cout<<endl;

	cout<<minimum(root)<<" is the minimum element in the tree"<<endl;
	cout<<maximum(root)<<" is the maximum element in the tree"<<endl;

	cout<<"successor of 50 is "<<sucessor(root,50)<<endl;
	cout<<"successor of 30 is"<<sucessor(root,30)<<endl;
	cout<<"successor of 40 is"<<sucessor(root,40)<<endl;
	cout<<"predecessor of 50 is "<<predecessor(root,50)<<endl;
	cout<<"predecessor of 30 is"<<predecessor(root,30)<<endl;
	cout<<"predecessor of 40 is"<<predecessor(root,40)<<endl;
	cout<<"enter the key to be deleted"<<endl;
	int x;cin>>x;
	delete_node(root,x);
	inorder(root);
	cout<<endl;
	cout<<height_of_tree(root);
	cout<<endl;

	cout<<"number of terms in the sequence"<<endl;
	int num;cin>>num;
	int a[num],b[num];
	for(int i=0;i<num;i++)
	{
		cin>>a[i];
		b[i]=a[i];
	}
	sort(b,b+num);
	if(is_sequence_valid(a,b[0],b[num-1],num,a[num-1])){cout<<"the given sequence is valid"<<endl;}
	else cout<<"sequence is invalid"<<endl;

}