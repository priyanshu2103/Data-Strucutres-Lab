#include <iostream>
#include <stdlib.h>
using namespace std;

typedef struct _node{
	int data;
	struct _node* next;
}node;

typedef struct _graph{
	int numVertices;
	struct _node** adjList;
}graph;

typedef struct _queue{
	struct _node* front;
	struct _node* rear;
}queue;

graph* createGraph(int vertices)
{
	graph* g=(graph*)malloc(sizeof(struct _graph));
	g->numVertices=vertices+1;
	g->adjList=(node**)malloc(((vertices+1)*sizeof(struct _node*)));

	for(int i=0;i<vertices;i++)
		g->adjList[i]=NULL;
	return g;
}

node* createNode(int x)
{
	node* p=(node*)malloc(sizeof(struct _node));
	p->data=x;
	p->next=NULL;
	return p;
}

void addEdge(graph* g,int src,int dest)
{
// 	node* temp=createNode(dest);
// 	if(g->adjList[src]==NULL)
// 	{
// 		g->adjList[src]=temp;
// 	}
// 	else
// 	{
// 		node* temp1=g->adjList[src];
// 		temp->next=temp1;
// 		g->adjList[src]=temp;
// 	}

	node* newNode=createNode(dest);
	newNode->next=g->adjList[src];
	g->adjList[src]=newNode;

	// node* newNode2=createNode(src);
	// newNode2->next=g->adjList[dest];
	// g->adjList[dest]=newNode2;
}


queue* createQueue()
{
	queue* q=(queue*)malloc(sizeof(struct _queue));
	q->front=NULL;
	q->rear=NULL;
	return q;
}

void push(queue* q,int data)
{
	node *temp = createNode(data); 
  
    // If queue is empty, then new node is front and rear both 
    if (q->rear == NULL) 
    { 
       q->front = q->rear = temp; 
       return; 
    } 
  
    // Add the new node at the end of queue and change rear 
    q->rear->next = temp; 
    q->rear = temp; 
}

node* pop(queue* q)
{
	// If queue is empty, return NULL. 
    if (q->front == NULL) 
       return NULL; 
  
    // Store previous front and move front one node ahead 
    node *temp = q->front; 
    q->front = q->front->next; 
  
    // If front becomes NULL, then change rear also as NULL 
    if (q->front == NULL) 
       q->rear = NULL; 
    return temp; 
}

bool is_queue_empty(queue* q)
{
	if(q->front==NULL)
		return true;
	else
		return false;
}

void BFS(graph* g,queue* q,string color[],int parent[],int distance[],int src)
{
	push(q,src);
	color[src]="grey";
	distance[src]=0;
	parent[src]=-1;

	while(!is_queue_empty(q))
	{
		node* temp=pop(q);
		int u=temp->data;
		node* temp2=g->adjList[u];
		while(temp2!=NULL)
		{
			if(color[temp2->data]=="white")
			{
				color[temp2->data]="grey";
				distance[temp2->data]=distance[u]+1;
				parent[temp2->data]=u;
				push(q,temp2->data);
			}
			temp2=temp2->next;
		}
		color[u]="black";
	}
	
}

int timer=0;

void DFS_visit(graph* g,string color[],int parent[],int discovered[],int finished[],int src)
{
	
	timer++;
	discovered[src]=timer;
	color[src]="grey";
	//cout<<src<<endl;
	node* temp=g->adjList[src];

	while(temp!=NULL)
	{
		if(color[temp->data]=="white")
		{
			cout<<"There's a tree edge from "<<src<<" to "<<temp->data<<endl;
			parent[temp->data]=src;
			DFS_visit(g,color,parent,discovered,finished,temp->data);
		}
		else if(color[temp->data]=="grey")
		{
			cout<<"There's a back edge from "<<src<<" to "<<temp->data<<endl;
		}

		else if(color[temp->data]=="black" && discovered[temp->data]<discovered[src])
			cout<<"There's a cross edge from "<<src<<" to "<<temp->data<<endl;

		else if(color[temp->data]=="black" && discovered[temp->data]>discovered[src])
			cout<<"There's a forward edge from "<<src<<" to "<<temp->data<<endl;

		temp=temp->next;
	}
	timer++;
	finished[src]=timer;
	color[src]="black";

}

void DFS(graph* g,int vertices,string color[],int parent[],int discovered[],int finished[],int src)
{
	for(int i=0;i<vertices;i++)
		if(color[i]=="white")
			DFS_visit(g,color,parent,discovered,finished,i);
}

int main()
{
	int vertices,edges;
	cin>>vertices>>edges;

	queue* q=createQueue();
	graph* g=createGraph(vertices);

	int src,c;
	cin>>src>>c;
	addEdge(g,src,c);

	int a,b;
	for(int i=0;i<edges-1;i++)
	{
		cin>>a>>b;
		addEdge(g,a,b);
	}

	string color[vertices];
	int parent[vertices];
	int distance[vertices];
	int discovered[vertices];
	int finished[vertices];

	for(int i=0;i<vertices;i++)
	{
		color[i]="white";
		parent[i]=-1;
		distance[i]=100000;
		discovered[i]=0;
		finished[i]=0;
	}

	// BFS(g,q,color,parent,distance,src);

	// for(int i=0;i<vertices;i++)
	// {
	// 	if(distance[i]>=0)
	// 	{
	// 		cout<<"distance of "<<i<<" from "<<src<<" is "<<distance[i]<<endl;
	// 	}
	// }

	DFS(g,vertices,color,parent,discovered,finished,src);

}	