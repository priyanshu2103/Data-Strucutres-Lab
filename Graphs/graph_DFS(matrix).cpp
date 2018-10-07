#include<iostream>
#include<stdlib.h>
using namespace std;

int timer=0;

void DFS_visit(int i,int adj[][100],int discovered[],string colour[],int final[],int parent[],int vertices)
{
	timer++;
	discovered[i]=timer;
	for(int j=1;j<=vertices;j++)
	{
		if(adj[i][j]==1)
		{
			if(colour[j]=="white")
			{
				cout<<i<<" --> "<<j<<" is a tree edge"<<endl;
				colour[j]="grey";
				parent[j]=i;
				DFS_visit(j,adj,discovered,colour,final,parent,vertices);
			}
			if(colour[j]=="grey")
				cout<<i<<" --> "<<j<<" is a back edge"<<endl;
			if(colour[j]=="black" && discovered[j]<discovered[i])
				cout<<i<<" --> "<<j<<" is a cross edge"<<endl;
			if(colour[j]=="black" && discovered[j]>discovered[i])
				cout<<i<<" --> "<<j<<" is a forward edge"<<endl;
		}	
	}

	colour[i]="black";
	timer++;
	final[i]=timer;
}

void DFS(int adj[][100],int discovered[],string colour[],int final[],int parent[],int vertices)
{
	for(int i=1;i<=vertices;i++)
	{
		colour[i]="white";
		parent[i]=-1;
		discovered[i]=0;
		final[i]=0;
	}
	for(int i=1;i<=vertices;i++)
		if(colour[i]=="white")
			DFS_visit(i,adj,discovered,colour,final,parent,vertices);
}

int main()
{
	int adj[100][100]={0};
	cout<<"Enter number of vertices and edges respectively"<<endl;
	int vertices;
	int edges;
	cin>>vertices>>edges;
	cout<<"Make connections"<<endl;

	int a,b;
	for(int i=0;i<edges;i++)
	{
		cin>>a>>b;
		adj[a][b]=1;
	}

	int discovered[vertices+1];
	string colour[vertices+1];
	int final[vertices+1];
	int parent[vertices+1];
	
	DFS(adj,discovered,colour,final,parent,vertices);

	for(int i=1;i<=vertices;i++)
		cout<<i<<" discovered at "<<discovered[i]<<" finished at "<<final[i]<<" successor of "<<parent[i]<<" of colour "<<colour[i]<<endl;
}