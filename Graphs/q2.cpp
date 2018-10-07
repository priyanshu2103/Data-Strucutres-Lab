#include <iostream>
#include <stdlib.h>
using namespace std;

typedef struct _stack{
	int data;
	struct _stack* next;
}stack;

typedef struct _list{
	int ascii;
	struct _list* next;
	struct right_linked_list* right;
}list;

typedef struct right_linked_list{
	char node;
	struct right_linked_list* next;
}right_list;

stack* push(stack* top,int data)
{
	stack* p=(stack*)malloc(sizeof(struct _stack));
	p->data=data;
	p->next=top;
	top=p;
	return top;
}

int pop(stack** top)
{
	if(*top==NULL)
		exit(1);
	else
	{
		char z=(*top)->data;
		stack* temp=*top;
		*top=(*top)->next;
		free(temp);
		return z;
	}
}

bool stack_empty(stack* top)
{
	if(top==NULL)
		return true;
	else
		return false;
}

int vertex_present[27]={0};
int discovered[27];
int finished[27];
string color[27];
char parent[27];
int time1=0;

list* createAdjacencyListVertices()
{
	list* adjList=(list*)malloc(sizeof(struct _list));
	adjList->right=NULL;
	adjList->ascii=0;
	adjList->next=NULL;
	int count=1;
	list* temp=adjList;

	for(int i=0;i<25;i++)
	{
		list* temp1=(list*)malloc(sizeof(struct _list));
		temp1->right=NULL;
		temp1->ascii=count;
		count++;
		temp1->next=NULL;
		temp->next=temp1;
		temp=temp1;
	}

	return adjList;
}

right_list* createNode(char c)
{
	right_list* p=(right_list*)malloc(sizeof(struct right_linked_list));
	p->node=c;
	p->next=NULL;
	return p;
}

void DFS_visit(int i,list* listHead,stack* top)
{
	top=push(top,i);

	while(!stack_empty(top))
	{
		int z=pop(&top);
		if(color[z]=="white")
			cout<<char(i+97)<<" ";
		color[z]="grey";
		time1++;
		discovered[z]=time1;
		list* temp5=listHead;
		
		int j=z;
		while(j--)
		{
			temp5=temp5->next;
		}

		right_list* temp6=temp5->right;
		while(temp6!=NULL)
		{
			if(color[temp6->node-'a']=="white")
			{
				push(top,temp6->node-'a');
			}
			temp6=temp6->next;
		}

	}
	color[i]="black";
	time1++;
	finished[i]=time1;
}

void DFS(list* listHead,stack* top)
{
	for(int i=0;i<27;i++)
	{
		discovered[i]=0;parent[i]='$';finished[i]=0;color[i]="white";
	}
	for(int i=0;i<27;i++)
	{
		if(vertex_present[i])
		{
			if(color[i]=="white")
			{
				DFS_visit(i,listHead,top);	
			}
		}
	}
}

int main()
{
	cout<<"Enter number of vertices and edges"<<endl;
	int vertices,edges;
	cin>>vertices>>edges;

	list* listHead=createAdjacencyListVertices();
	char a,b;

	for(int i=0;i<edges;i++)
	{
		cin>>a>>b;
		vertex_present[a-'a']=1;
		list* temp2=listHead;

		while(temp2->ascii!=a-'a')
			temp2=temp2->next;
		right_list* temp3=temp2->right;

		if(temp3==NULL)
		{
			right_list* temp4=createNode(b);
			temp2->right=temp4;
		}
		else
		{
			while(temp3->next!=NULL)
				temp3=temp3->next;
			right_list* temp4=createNode(b);
			temp3->next=temp4;
		}
	}

	stack* top=NULL;

	DFS(listHead,top);
}