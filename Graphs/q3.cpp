#include<bits/stdc++.h>
using namespace std;

struct QNode 
{ 
    int key; 
    struct QNode *next; 
}; 
  
// The queue, front stores the front node of LL and rear stores ths 
// last node of LL 
struct Queue 
{ 
    struct QNode *front, *rear; 
}; 
  
// A utility function to create a new linked list node. 
struct QNode* newNode(int k) 
{ 
    struct QNode *temp = (struct QNode*)malloc(sizeof(struct QNode)); 
    temp->key = k; 
    temp->next = NULL; 
    return temp;  
} 
  
// A utility function to create an empty queue 
struct Queue *createQueue() 
{ 
    struct Queue *q = (struct Queue*)malloc(sizeof(struct Queue)); 
    q->front = q->rear = NULL; 
    return q; 
} 
  
// The function to add a key k to q 
void push(struct Queue *q, int k) 
{ 
    // Create a new LL node 
    struct QNode *temp = newNode(k); 
  
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
  
// Function to remove a key from given queue q 
void pop(struct Queue *q) 
{ 
    // If queue is empty, return NULL. 
    // if (q->front == NULL) 
    //    return NULL; 
  
    // Store previous front and move front one node ahead 
    struct QNode *temp = q->front; 
    int z=temp->key;
    q->front = q->front->next; 
  
    // If front becomes NULL, then change rear also as NULL 
    if (q->front == NULL) 
       q->rear = NULL; 
  	free(temp);
    
} 

int top(Queue* q)
{
	return q->front->key;
}

bool queue_empty(Queue* q)
{
	if(q->front==NULL)
	{
		return true;
	}
	else return false;
}


int visited[100]={0};


void BFS(int adj[][100],int vertices,int key,struct Queue *q,int destination)
{
	int visited[100]={0};
	if(key==destination)
	{
		cout<<destination<<" can be reached from "<<key<<endl;return ;
	}
	
	push(q,key);
	visited[key]=1;
	while(!queue_empty(q))
	{
		int j=top(q);pop(q);
		//cout<<j<<endl;
		for(int k=1;k<=vertices;k++)
		{
			if(adj[j][k]==1 && k==destination)
			{
				cout<<destination<<" can be reached from "<<key<<endl;
				return ;
			}
			if(adj[j][k]==1 && visited[k]==0)
			{
				push(q,k);
				visited[k]=1;
			}
		}
	}
	cout<<destination<<" can not be reached from "<<key<<endl;return ;

}

void empty_the_queue(Queue* q)
{
	while(!queue_empty(q))
	{
		pop(q);
	}
}

int main()
{
	struct Queue *q = createQueue();
	int vertices,edges;
	cin>>vertices>>edges;
	int a,b;
	int adj[vertices+1][100]={0};
	for(int i=0;i<edges;i++)
	{
		cin>>a>>b;
		adj[a][b]=1;
	}
	cout<<endl;
	for(int i=1;i<=vertices;i++)
	{
		for(int j=1;j<=vertices;j++)
		{
			cout<<adj[i][j]<<" ";
		}
		cout<<endl;
	}

	for(int i=1;i<=vertices;i++)
	{
		for(int j=1;j<=vertices;j++)
		{
			BFS(adj,vertices,i,q,j);
			empty_the_queue(q);
		}
	}
	
}