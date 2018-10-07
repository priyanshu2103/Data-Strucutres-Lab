#include <bits/stdc++.h>
using namespace std;

class Graph{

	int vertices;
	vector<int> *v;
	string *color;
	int *dist;
	int *discovery;
	int *finished;
	int *predecessor;
	int time;

public:

	Graph(int a);
	void addEdge(int source,int dest);
	//void deleteEdge(int source,int dest);
	void BFS(int src);
	void DFS();
	void DFS_visit(int i);
};

Graph::Graph(int a){

	this->vertices=a;
	v= new vector<int>[vertices];
	color=new string[vertices];
	dist=new int[vertices];
	discovery=new int[vertices];
	finished=new int[vertices];
	predecessor=new int[vertices];
	time=0;

}

void Graph::addEdge(int source,int dest)
{
	v[source].push_back(dest);
	
}

void Graph::BFS(int src){

	int dist[this->vertices]={0};
	int parent[this->vertices];

	for(int i=0;i<this->vertices;i++)
		color[i]="white";
	
	for(int i=0;i<this->vertices;i++)
		parent[i]=-1000;	

	queue<int> q;

	color[src]="grey";
	dist[src]=0;
	q.push(src);
	cout<<" "<<src;

	while(!q.empty()){
		int a=q.front();
		q.pop();

		int x=v[a].size();
		for(int i=0;i<x;i++)
		{
			if(color[v[a][i]]=="white"){
				color[v[a][i]]="grey";
				dist[v[a][i]]=dist[a]+1;
				parent[v[a][i]]=a;
				cout<<" "<<v[a][i];
				q.push(v[a][i]);
			}
		}

		color[a]="black";
	}

}

void Graph::DFS_visit(int i){
	time++;

	this->discovery[i]=time;
	color[i]="grey";
	int size=v[i].size();

	for(int j=0;j<size;j++)
	{
		if(color[v[i][j]]=="white"){
			cout<<"There's a tree edge from "<<i<<" to "<<v[i][j]<<endl;
			predecessor[v[i][j]]=i;
			DFS_visit(v[i][j]);
		}
		else if(color[v[i][j]]=="grey"){
			cout<<"There's a back edge from "<<i<<" to "<<v[i][j]<<endl;
		}
		else if(color[v[i][j]]=="black" && discovery[v[i][j]]<discovery[i]){
			cout<<"There's a  cross edge from "<<i<<" to "<<v[i][j]<<endl;
		}
		else if(color[v[i][j]]=="black" && discovery[v[i][j]]>discovery[i]){
			cout<<"There's a forward edge from "<<i<<" to "<<v[i][j]<<endl;
		}
	}
	time++;
	finished[i]=time;
	color[i]="black";

}

void Graph::DFS(){

	for(int i=0;i<vertices;i++)
		color[i]="white";	
	for(int i=0;i<vertices;i++)
		dist[i]=0;
	for(int i=0;i<vertices;i++)
		predecessor[i]=-1000;
	for(int i=0;i<vertices;i++)
		discovery[i]=0;
	for(int i=0;i<vertices;i++)
		finished[i]=0;
	

	for(int i=0;i<this->vertices;i++)
	{
		if(color[i]=="white")
			DFS_visit(i);
	}
}




