//DFS traversal along with classification of edges of DFS forest

#include<iostream>
#include<stdlib.h>
using namespace std;

int timer=0;

void DFS_visit(int i,int adj[][100],int vertices,int parent[],string color[],int discovered[],int final[])
{
	color[i]="grey";
	timer++;
	discovered[i]=timer;
	for(int j=1;j<=vertices;j++)
	{
		if(adj[i][j]==1)
		{
			if(color[j]=="white")
			{
				cout<<i<<"-"<<j<<" is a tree edge"<<endl;
				parent[j]=i;
				DFS_visit(j,adj,vertices,parent,color,discovered,final);
			}
			if(color[j]=="grey")
			{
				cout<<i<<"-"<<j<<" is a back edge"<<endl;
			}
			if(color[j]=="black" && discovered[i]>discovered[j])
			{
				cout<<i<<"-"<<j<<" is a cross edge "<<endl;
			}
			if(color[j]=="black" && discovered[i]<discovered[j])
			{
				cout<<i<<"-"<<j<<" is a forward edge"<<endl;
			}
		}
	}
	timer++;color[i]="black";final[i]=timer;
}


void DSF(int vertices,string color[],int parent[],int discovered[],int final[],int adj[][100])
{
	for(int i=1;i<=vertices;i++)
	{
		color[i]="white";parent[i]=-1;discovered[i]=0;final[i]=0;
	}
	for(int i=1;i<=vertices;i++)
	{
		if(color[i]=="white")
		{
			DFS_visit(i,adj,vertices,parent,color,discovered,final);
		}
	}
}



int main()
{
	int vertices,edges;
	cin>>vertices>>edges;
	int adj[vertices+1][100]={0};
	int a,b;

	for(int i=0;i<edges;i++)
	{
		cin>>a>>b;
		adj[a][b]=1;
		//adj[b][a]=1;
	}

	string color[vertices+1];
	int discovered[vertices+1];
	int parent[vertices+1];
	int final[vertices+1];

	DSF(vertices,color,parent,discovered,final,adj);
	
	for(int i=1;i<=vertices;i++)
	{
		cout<<discovered[i]<<" "<<final[i]<<" "<<parent[i]<<" "<<color[i]<<endl;
	}
	//print_path(8,7,parent);
	//cout<<endl;
	//print_path(2,7,parent);
}