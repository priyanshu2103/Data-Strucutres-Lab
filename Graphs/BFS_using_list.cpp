//BSF using adjacent list and also problem 1 of practise papre
#include<bits/stdc++.h>
using namespace std;
//queue

typedef struct node
{
	char key;
	struct node* next;
}node;

struct Queue
{
	struct node *front,*rear;
};

struct Queue* createQueue()
{
	struct Queue* temp=(Queue*)malloc(sizeof(Queue));
	temp->front=temp->rear=NULL;
	return temp;
}


void push(struct Queue* q,char n)
{
	struct node* temp=(node*)malloc(sizeof(node));
	temp->key=n;
	temp->next=NULL;
	if(q->rear==NULL)
	{
		q->rear=q->front=temp;
	}
	q->rear->next=temp;
	q->rear=temp;

}

char pop(struct Queue* q)
{
	if(q->front==NULL)
	{
		return 0;
	}
	else
	{
		struct node* temp=q->front;
		q->front=q->front->next;
		if(q->front==NULL){q->rear=NULL;}
		char z=temp->key;
		free(temp);
		return z;
	}
}

bool queue_empty(Queue* q)
{
	if(q->front==NULL && q->rear==NULL)
	{
		return true;
	}
	else return false;
}

//queue finish

int distance1[27];
string color[27];
char parent[27];

struct vertex_of_graph
{
	char vertex;
	struct vertex_of_graph* next;
	struct node_of_list* right;
};

struct node_of_list
{
	char node;
	struct node_of_list* next;
};

struct vertex_of_graph* create_vertex(char c)
{
	struct vertex_of_graph* temp=(vertex_of_graph*)malloc(sizeof(vertex_of_graph));
	temp->vertex=c;
	temp->next=NULL;
	temp->right=NULL;
	return temp;
}

struct node_of_list* create_node(char c)
{
	struct node_of_list* temp=(node_of_list*)malloc(sizeof(node_of_list));
	temp->node=c;
	temp->next=NULL;
	return temp;
}

void BFS(struct Queue* q,struct vertex_of_graph* temporary)
{
	push(q,temporary->vertex);
	color[temporary->vertex-'a']="grey";
	distance1[temporary->vertex-'a']=0;
	while(!queue_empty(q))
	{
		char z=pop(q);
		struct vertex_of_graph* temp6=temporary;
		while(temp6->vertex!=z)
		{
			temp6=temp6->next;
		}
		struct node_of_list* temp7=temp6->right;
		while(temp7!=NULL)
		{
			if(color[temp7->node-'a']=="white")
			{	
				push(q,temp7->node);
				color[temp7->node-'a']="grey";
				distance1[temp7->node-'a']=distance1[z-'a']+1;
				parent[temp7->node-'a']=z;
			}
			temp7=temp7->next;
		}
		color[z-'a']="black";
	}
}

int main()
{
	struct Queue *q = createQueue();
	int vertices,edges;
	cin>>vertices>>edges;
	int vertex_present[27]={0};
	char x,v,u;
	cin>>x>>v;
	//cout<<x<<v;
	vertex_present[x-'a']=1;
	//cout<<x-'a'<<endl;
	struct vertex_of_graph* graph=create_vertex(x);
	struct node_of_list* temp=create_node(v);
	graph->right=temp;
	
	struct vertex_of_graph* temporary=graph;
														//it is for directed graph for directed simply make more vertices and it is rather easy
	for(int i=0;i<edges-1;i++)
	{
		cin>>u>>v;
		if(vertex_present[u-'a'])
		{
			struct vertex_of_graph* temp1=graph;
			//cout<<temp1->vertex<<endl;
			while(temp1->vertex!=u)
			{
				temp1=temp1->next;
			}
			struct node_of_list* temp2=temp1->right;
			while(temp2->next!=NULL)
			{
				temp2=temp2->next;
			}
			struct node_of_list* temp3=create_node(v);
			temp2->next=temp3;
		}
		else 
		{
			struct vertex_of_graph* temp4=create_vertex(u);
			//cout<<temp4->vertex<<endl;
			vertex_present[u-'a']=1;
			struct vertex_of_graph* temp1=temporary;
			while(temp1->next!=NULL)
			{
				temp1=temp1->next;
			}
			temp1->next=temp4;
			struct node_of_list* temp5=create_node(v);
			temp4->right=temp5;
		}
	} 
	for(int i=0;i<27;i++)
	{
		color[i]="white";
		parent[i]=-1;
		distance1[i]=-1;
	}

	BFS(q,temporary);
	for(int i=0;i<27;i++)
	{
		if(distance1[i]>=0)
		{
			cout<<"distance of "<<(char)(i+97)<<" from "<<x<<" is "<<distance1[i]<<endl;
		}
	}
}