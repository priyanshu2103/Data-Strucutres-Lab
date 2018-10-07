#include<iostream>
#include <stdlib.h>
using namespace std;

typedef struct node
{
	int key;
	struct node* next;
}node;

typedef struct Queue
{
	node *front,*rear;
}queue;

struct Queue* createQueue()
{
	struct Queue* temp=(Queue*)malloc(sizeof(Queue));
	temp->front=temp->rear=NULL;
	return temp;
}


void push(queue* q,int n)
{
	node* temp=(node*)malloc(sizeof(node));
	temp->key=n;
	temp->next=NULL;
	if(q->rear==NULL)
	{
		q->rear=q->front=temp;
	}
	q->rear->next=temp;
	q->rear=temp;

}

int pop(queue* q)
{
	if(q->front==NULL)
	{
		return 0;
	}
	else
	{
		node* temp=q->front;
		q->front=q->front->next;
		if(q->front==NULL){q->rear=NULL;}
		int z=temp->key;
		free(temp);
		return z;
	}
}

bool queue_empty(queue* q)
{
	if(q->front==NULL && q->rear==NULL)
	{
		return true;
	}
	else return false;
}

//int vertices;
void BSF(int vertices,int adj[][100],int distance[],string color[],int parent[],int key,queue *q)
{
	for(int i=1;i<=vertices;i++)
	{
		color[i]="white";distance[i]=0;parent[i]=-1;
	}

	distance[key]=0;push(q,key);color[key]="grey";

	while(!queue_empty(q))
	{
		int j=pop(q);

		for(int k=1;k<=vertices;k++)
		{
			if(adj[j][k]==1 && color[k]=="white")
			{
				push(q,k);
				color[k]="grey";
				distance[k]=distance[j]+1;
				parent[k]=j;
			}
		}
		color[j]="black";
	}

}

void print_path(int node,int key,int parent[])
{
	if(parent[node]!=-1)
	{
		print_path(parent[node],key,parent);
	}	
	cout<<node<<" --> ";
}


int main()
{
	queue *q = createQueue();

	int vertices,edges;
	cin>>vertices>>edges;
	int adj[vertices+1][100]={0};
	int a,b;
	
	for(int i=0;i<edges;i++)
	{
		cin>>a>>b;
		adj[a][b]=1;
		adj[b][a]=1;
	}

	string color[vertices+1];
	int distance[vertices+1];
	int parent[vertices+1];

	BSF(vertices,adj,distance,color,parent,1,q);

	for(int i=1;i<=vertices;i++)
	{
		cout<<distance[i]<<" "<<parent[i]<<" "<<color[i]<<endl;
	}

	print_path(8,7,parent);
	cout<<endl;
	print_path(2,7,parent);
}