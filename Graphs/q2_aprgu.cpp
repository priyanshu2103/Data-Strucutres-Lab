#include <iostream>
#include <stdlib.h>
using namespace std;

typedef struct _stack
{
	int data;
	struct _stack* next;
}node;

node* top=NULL;

int top_value()
{
	node* temp=top;
	int data=temp->data;
	return data;
}

bool stack_empty()
{
	if(top==NULL)
	{
		return true;
	}
	return false;
}
int pop()
{
	if(top==NULL){cout<<"empty stack"<<endl;}
	else {
		node* temp=top;
		int data=temp->data;
		top=top->next;
		free(temp);
		return data;
	}
}

void push(int data)
{
	node* q=(node*)malloc(sizeof(node));
	q->data=data;
	q->next=NULL;
	if(top==NULL){top=q;}
	else {
		q->next=top;
		top=q;
	}
}

int vertex_present[27]={0};
int discovered[27];
int final[27];
string color[27];
char parent[27];
int time1=0;

struct vertex_of_graph
{
	int ascii;
	struct vertex_of_graph* next;
	struct node_of_vertex* right;
};

struct node_of_vertex
{
	char node;
	struct node_of_vertex* next;
};

struct vertex_of_graph* create_vertices()
{
	struct vertex_of_graph* graph=(struct vertex_of_graph*)malloc(sizeof(vertex_of_graph));
	graph->right=NULL;
	graph->ascii=0;				//first vertex is of a
	graph->next=NULL;
	struct vertex_of_graph* temp=graph;
	int count=1;
	for(int i=0;i<25;i++)
	{
		struct vertex_of_graph* temp1=(struct vertex_of_graph*)malloc(sizeof(vertex_of_graph));
		temp1->right=NULL;
		temp1->ascii=count;
		temp1->next=NULL;
		count++;
		temp->next=temp1;
		temp=temp1;
	}
	return graph;
}

struct node_of_vertex* create_node(char c)
{
	struct node_of_vertex* temp=(node_of_vertex*)malloc(sizeof(node_of_vertex));
	temp->node=c;
	temp->next=NULL;
	return temp;
}

void DFS_VISIT(int i,struct vertex_of_graph* graph)
{
	//if(vertex_present[i])
	// //{	
	// 	time1++;
	// 	discovered[i]=time1;
	// 	color[i]="grey";
		
		push(i);
		
		
		while(!stack_empty())
		{
			int j=pop();
			if(color[j]=="white")cout<<(char)(j+97)<<" ";		//store them in a array then check consecutive elements if edge between them then it is a tree edge
			color[j]="grey";
			time1++;
			discovered[j]=time1;
			struct vertex_of_graph* temp=graph;
			int k=j;
			while(k--)
			{
				temp=temp->next;
			}
			
			struct node_of_vertex* temp1=temp->right;
			while(temp1!=NULL)
			{
				if(color[temp1->node-'a']=="white")
				{
					//parent[temp1->node-'a']=(char)(j+97);
					//cout<<"("<<(char)(j+97)<<","<<temp1->node<<")"<<"is a tree edge"<<endl;
					push(temp1->node-'a');
					//break;
				}
				temp1=temp1->next;
			}
		}
		
		color[i]="black";time1++;final[i]=time1;
	//}
}

void DFS(struct vertex_of_graph* graph)
{
	for(int i=0;i<27;i++)
	{
		final[i]=0;discovered[i]=0;parent[i]='#';color[i]="white";
	}
	struct vertex_of_graph* temp4=graph;
	for(int i=0;i<27;i++)
	{
		if(vertex_present[i] && color[i]=="white")
		{
			DFS_VISIT(i,graph);
		}
	}
}

int main()
{
	int vertices,edges;
	cin>>vertices>>edges;
	struct vertex_of_graph* graph=create_vertices();
	//cout<<"q"<<endl;
	char a,b;
	for(int i=0;i<edges;i++)
	{
		cin>>a>>b;
		vertex_present[a-'a']=1;
		struct vertex_of_graph* temp1=graph;
		while(temp1->ascii!=a-'a')
		{
			temp1=temp1->next;
		}
		struct node_of_vertex* temp2=temp1->right;
		if(temp2==NULL)
		{
			struct node_of_vertex* temp3=create_node(b);
			temp1->right=temp3;
		}
		else if(temp2!=NULL)
		{
			while(temp2->next!=NULL)
			{
				temp2=temp2->next;
			}
			struct node_of_vertex* temp3=create_node(b);
			temp2->next=temp3;
		}
	}
	DFS(graph);
}