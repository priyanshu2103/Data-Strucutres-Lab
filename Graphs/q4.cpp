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
	g->numVertices=vertices+1;
	g->adjList=(node**)malloc(((vertices+1)*sizeof(struct _node*)));

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

	node* newNode2=createNode(src);
	newNode2->next=g->adjList[dest];
	g->adjList[dest]=newNode2;
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

bool is_graph_bipartite(graph* g,int vertices,int src,queue* q,int color[])
{
	color[src]=1;
	push(q,src);
	while(!is_queue_empty(q))
	{
		node* u=pop(q);
		//cout<<u->vertex<<endl;
		node* temp=g->adjList[u->vertex];
		//cout<<temp->vertex<<endl;
		
		for(int i=0;i<vertices+1;i++)
		{
			if(temp!=NULL && color[temp->vertex]==-1)
			{
				color[temp->vertex]=1-color[u->vertex];
				push(q,temp->vertex);
				temp=temp->next;
			}
			else if(temp!=NULL && color[temp->vertex]==color[u->vertex])
				return false;
		}
	}
	return true;
}

int main()
{
	cout<<"Give the values of n and r"<<endl;
	int vertices,edges;
	cin>>vertices>>edges;

	graph* graph=createGraph(vertices);

	int src,d;
	cin>>src>>d;
	addEdge(graph,src,d);
	int a,b;
	for(int i=0;i<edges-1;i++)
	{
		cin>>a>>b;
		addEdge(graph,a,b);
	}
	queue* q=createQueue();

	int color[vertices+1];
	for(int i=0;i<vertices+1;i++)
		color[i]=-1;

	if(is_graph_bipartite(graph,vertices,src,q,color))
	{
		for(int i=1;i<=vertices;i++)
		{
			if(color[i]==1)
				cout<<i<<" is a good guy"<<endl;
			else
				cout<<i<<" is a bad guy"<<endl;
		}
	}
	else
		cout<<"Not possible"<<endl;

}