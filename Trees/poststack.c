# include<stdio.h>
# include<stdlib.h>
typedef struct node {
	int data;
	struct node * left;
	struct node *right;
}node;
typedef struct stack
{
	node *data1;
	struct stack *next; 
}stack;
stack *push(node *temp,stack *top)
{
	stack *p=(stack *)malloc(sizeof(stack));
	p->data1=temp;
	p->next=top;
	top=p;
	return top;
}
node *pop(stack **top)
{
	stack *temp=*top;
	*top=(*top)->next;
	node *new=temp->data1;
	free(temp);
	return new;
}
node *createNode(int x)
{
	node *temp=(node *)malloc(sizeof(struct node));
	temp->data=x;
	temp->left=NULL;
	temp->right=NULL;
}
node *makeRoot()
{
	int x;
	printf("Enter root\n");
	scanf("%d",&x);
	node *temp=createNode(x);
	return temp;
}
node *find(int x,node *root)
{
	if(root->data==x) return root;
	if(root!=NULL)
	{
		if(root->left!=NULL&&find(x,root->left)!=NULL)
		{
			return find(x,root->left);
		}
		if(root->right!=NULL&&find(x,root->right)!=NULL)
		{
			return find(x,root->right);
		}
	}
	return NULL;
}
node *add(int x,int y,char c,node *root)
{
	node *temp=(node *)malloc(sizeof(node));
	temp=find(x,root);
	if(temp==NULL)
	{
		printf("error\n");
		return NULL;
	}
	if(c=='L')
	{
		if(temp->left==NULL) 
		{
			temp->left=createNode(y);
			return root;
		}
		else return NULL;
	}
	else
	{
		if(temp->right==NULL) 
		{
			temp->right=createNode(y);
			return root;
		}
		else return NULL;
	}
}
void postorder(node * p,stack *top)
{
	node *q;
	stack *k;
	do
	{
		while(p!=NULL)
		{
				top=push(p,top);
				p=p->left;
		}
		if(top!=NULL)
		{
			p=pop(&top);
			q=p;
			p=p->right;
			if(p==NULL) 
			{
				printf("%d ",q->data);
				if(top!=NULL&&top->data1->right==q)
				{
					top->data1->right=NULL;
				}
			}
			else
			{
				top=push(q,top);
			}
		}
	}while(p!=NULL||top!=NULL);
}
int main()
{
	stack *top=NULL;
	node *root=makeRoot();
	int a,b,i;
	char c;
	do
	{
		printf("Enter num1,num2,L/R\n");
		scanf("%d %d %c",&a,&b,&c);
		root=add(a,b,c,root);
		printf("Enter 1 to continue\n");
		scanf("%d",&i);
	}
	while(i==1);
	postorder(root,top);
	return 0;
}