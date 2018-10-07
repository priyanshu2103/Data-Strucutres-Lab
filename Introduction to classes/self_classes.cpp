#include <bits/stdc++.h>
#include "self_graph.h"

using namespace std;

int main()
{
	Graph g(8);
	g.addEdge(0,1);
	g.addEdge(1,2);
	g.addEdge(2,3);
	g.addEdge(3,1);
	g.addEdge(1,4);
	g.addEdge(0,4);
	g.addEdge(5,6);
	g.addEdge(5,7);
	g.addEdge(7,6);
	g.addEdge(6,0);

	g.DFS();
}