#include <iostream>
#include <stdlib.h>
using namespace std;

typedef struct _node{
	struct _node* next;
	int vertex;
}node;

typedef struct _graph
{
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
	g->numVertices=vertices;
	g->adjList=(node**)malloc(((vertices)*sizeof(struct _node*)));

	for(int i=0;i<vertices;i++)
		g->adjList[i]=NULL;
	return g;
}

node* createNode(int x)
{
	node* p=(node*)malloc(sizeof(struct _node));
	p->vertex=x;
	p->next=NULL;
	return p;
}

void addEdge(graph* g,int src,int dest)
{
	node* newNode=createNode(dest);
	newNode->next=g->adjList[src];
	g->adjList[src]=newNode;
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

void printCycle(graph* g,int predecessor[],int from,int to)
{
	if(predecessor[to]!=from)
	{
		printCycle(g,predecessor,from,predecessor[to]);
		cout<<predecessor[to]<<" ";
	}
	cout<<endl;
}

void DFS_visit(graph* g,string color[],int predecessor[],int start)
{
	node* temp=g->adjList[start];
	//cout<<temp->vertex<<endl;
	color[temp->vertex]="grey";
	//temp=temp->next;

	while(temp!=NULL)
	{
		if(color[temp->vertex]=="white")
		{
			color[temp->vertex]="grey";
			predecessor[temp->vertex]=start;
			DFS_visit(g,color,predecessor,temp->vertex);
		}
		else if(color[temp->vertex]=="grey")
		{
			printCycle(g,predecessor,temp->vertex,temp->vertex);
		}
	}
}

void DFS(graph* g,string color[],int predecessor[],int vertices)
{
	for(int i=0;i<vertices;i++)
	{
		//node* temp=g->adjList[i];
		//cout<<temp->vertex<<endl;
		if(color[i]=="white")
			DFS_visit(g,color,predecessor,i);
	}
}

int main()
{
	cout<<"Enter number of vertices"<<endl;
	int vertices;
	cin>>vertices;

	graph* graph=createGraph(vertices);

	cout<<"Start giving inputs, press -1 to quit"<<endl;
	int a=-1;
	int b;
	do{
		cin>>a>>b;
		if(a!=-1)
			addEdge(graph,a,b);
	}while(a!=-1);

	string color[vertices];
	int predecessor[vertices];

	for(int i=0;i<vertices;i++)
	{
			color[i]="white";
			predecessor[i]=-1;
	}

	DFS(graph,color,predecessor,vertices);
}