#include <stdio.h>
#include <stdlib.h>
typedef struct _node{
	int data;
	struct _node * left;
	struct _node * right;
	struct _node * parent;
}node;

node * createNode(int data);
void insert(int key,node * root);
void printInorder(node * root);
void printPreorder(node * root);
node * search(int key, node * root);
node * max(node * root);
node * min(node * root);
node * pred(node * x,node * root);
node * succ(node * x,node * root);
void delete(node * temp,node ** root);
void MorrisInorder(node * root);
void MorrisPreorder(node * root);
int countLeaves(node * root);
int height(node * root);
node * LCA(node * root,int n1, int n2);
node * lca(node * root, node * temp1, node * temp2);

/*-----------------------------------------------------*/
void main()
{
	/*creating root node*/
	node * root;
	int n;
	printf("Enter root node\n");
	scanf("%d",&n);
	root=createNode(n);


	/*Entering subsequent nodes*/
	printf("Enter subsequent numbers/-1 to exit\n");
	while(n!=-1)
	{
		scanf("%d",&n);
		if(n!=-1)
			insert(n,root);
	}

	/*Printing in and pre orders*/
	printf("\n");
	printInorder(root);
	printf("\n");
	printPreorder(root);
	printf("\n");
	MorrisPreorder(root);
	printf("\n");

	/*checking search function*/
	printf("Enter element you want to search\n");
	scanf("%d",&n);
	node * temp = search(n,root);
	if(temp!=NULL)
		printf("%d Found\n",temp->data );
	
	printf("Enter element you want to search\n");
	scanf("%d",&n);
	temp = search(n,root);
	if(temp!=NULL)
		 printf("%d Found\n",temp->data );

	//printing max and min
	temp = max(root);
	printf("Max = %d\n",temp->data);

	temp = min(root);
	printf("Min = %d\n",temp->data);

	/*check predecessor and successor*/
	/*printf("Enter number whose predecessor you want to find :\n");
	scanf("%d",&n);
	temp = search(n,root);
	temp = pred(temp,root);
	if(temp!=NULL)
	printf("%d is the predecessor of %d\n",temp->data,n);
	else
		printf("%d has no predecessor\n",n );

	printf("Enter number whose successor you want to find :\n");
	scanf("%d",&n);
	temp = search(n,root);
	temp = succ(temp,root);
	if(temp!=NULL)
	printf("%d is the successor of %d\n",temp->data,n);
	else
		printf("No successor\n");

	/*Checking delete*/
	/*printf("Enter element you want to delete\n");
	scanf("%d",&n);
	temp=search(n,root);
	delete(temp,&root);
	if(root!=NULL)
	printInorder(root);
	printf("\n");

	printf("Enter element you want to delete\n");
	scanf("%d",&n);
	temp=search(n,root);
	delete(temp,&root);
	if(root!=NULL)
	printInorder(root);
	printf("\n");
	MorrisInorder(root);*/
	printf("\n");
	printf("No. of leaves = %d\n",countLeaves(root) );
	printf("Height = %d\n",height(root) );

	printf("Enter 2 numbers whose LCA you want to find\n");
	int n1,n2;
	scanf("%d %d",&n1,&n2);
	temp = LCA(root,n1,n2);
	if(temp!=NULL)
		printf("%d is LCA\n",temp->data );
	else
		printf("Error\n");
}
/*-----------------------------------------------------*/

node * createNode(int data)
{
	node * temp = (node *)malloc(sizeof(node));
	temp->data=data;
	temp->left=temp->right=temp->parent=NULL;
	return temp;
}

void insert(int key,node * root)
{
	node * p = NULL;
	while(root!=NULL)
	{
		if(root->data > key)
		{
			p=root;
			root=root->left;
		}
		else
		{
			p=root;
			root=root->right;
		}
	}
	root = createNode(key);
	root->parent=p;
	if(p->data > root->data)   p->left = root;
	else                       p->right = root;
}

void printPreorder(node * root)
{
	if(root==NULL) return;

	printf("%d ",root->data );
	printPreorder(root->left);
	printPreorder(root->right);
}

void printInorder(node * root)
{
	if(root == NULL) return;

	printInorder(root->left);
	printf("%d ",root->data);
	printInorder(root->right);
}

node * search(int key, node * root)
{
	if(root==NULL) 
		{
			printf("%d Not found\n",key);
			return NULL;
		}
	if(root->data == key) return root;

	if(key < root->data)
		search(key,root->left);
	else
		search(key,root->right);
}

node * max(node * root)
{
	if(root==NULL) return NULL;
	while(root->right!=NULL)
		root=root->right;

	return root;
}

node * min(node * root)
{
	if(root==NULL) return NULL;

	while(root->left!=NULL)
		root=root->left;

	return root;
}

node * pred(node * x,node * root)
{
	if(x==NULL || x==min(root)) return NULL;


	if(x->left!=NULL )
	{
		return max(x->left);
	} 
	else
	{
		node * p = x->parent;
		while(p!=NULL && x==p->left)
		{	
			x=p;
			p = p->parent;
		}

		return p;
	}
}

node * succ(node * x,node * root)
{
	if(x==NULL || x==max(root)) return NULL;

	if(x->right!=NULL)
		return min(x->right);

	else
	{
		node * s = x->parent;
		while(s!=NULL && x==s->right)
		{
			x=s;
			s=s->parent;
		}
		return s;
	}
}

void delete(node * temp,node ** root)
{

	if(temp==NULL) return;

	if(temp->left==NULL && temp->right==NULL)
	{
		if(temp!=*root)
		{
			node * p = temp->parent;
			if(p->right == temp)
				p->right=NULL;
			else
				p->left=NULL;
			
			temp->parent=NULL;
		}
		else 
			*root=NULL;
		
		free(temp);
	}

	else if (temp->right!=NULL && temp->left == NULL)
	{
		node * next = temp->right;
		if(temp!=(*root))
		{
			next->parent=temp->parent;
			
			if(temp==temp->parent->left)
				temp->parent->left=next;

			else
				temp->parent->right=next;
		}
		if(temp==*root)
		{
			*root=next;
			next->parent=NULL;
		}
		free(temp);
	}
	else if(temp->left!=NULL && temp->right == NULL)
	{
		node * next = temp->left;
		if(temp!=(*root))
		{
			next->parent=temp->parent;

			if(temp==temp->parent->left)
				temp->parent->left=next;

			else
				temp->parent->right=next;
		}
		if(temp==*root)
		{
			*root = next;
			next->parent=NULL;
		}
		free(temp);
	}
	else
	{
		node * s = succ(temp,*root);
		temp->data = s->data;
		delete(s,root);
	}

}

void MorrisInorder(node * root)
{
	if(root==NULL) return;

	node * p = root;

	while(p!=NULL)
	{
		if(p->left==NULL)
		{
			printf("%d ",p->data);
			p=p->right;
		}
		else
		{
			node * pred = p->left;

			while(pred->right!=NULL && pred->right!=p)
				pred=pred->right;

			if(pred->right==NULL)
			{
				pred->right=p;
				p=p->left;
			}
			else
			{
				pred->right=NULL;
				printf("%d ",p->data );
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
			printf("%d ",p->data );
			p=p->right;
		}
		else
		{
			node * pred = p->left;

			while(pred->right!=NULL && pred->right!=p)
				pred=pred->right;

			if(pred->right==NULL)
			{
				printf("%d ",p->data );
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

int countLeaves(node * root)
{
	if(root==NULL) return 0;

	if(root->right==NULL && root->left == NULL)
		return 1;

	return countLeaves(root->left) + countLeaves(root->right);
}

int height(node * root)
{
	if(root==NULL) return 0;

	int lheight=height(root->left);
	int rheight=height(root->right);

	if(lheight > rheight)
		return lheight+1;
	else
		return rheight+1;
}

node * LCA(node * root,int n1, int n2)
{
	node * temp1 = search(n1,root);
	node * temp2 = search(n2,root);

	if(temp1!=NULL && temp2!=NULL)
		return	lca(root,temp1,temp2);
	else
		return NULL;
}

node * lca(node * root, node * temp1, node * temp2)
{
	if(root==NULL) return NULL;

	if(root==temp1 || root==temp2) return root;

	node * left = lca(root->left,temp1,temp2);
	node * right = lca(root->right,temp1,temp2);

	if(left!=NULL && right!=NULL) return root;
	if(left == NULL && right ==NULL) return NULL;

	if(left!=NULL) return left;
	else 		   return right;
}