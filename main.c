#include <stdio.h>
#include <stdlib.h>

#include "GraphInterface.h"

// Driver program to test above functions
int main()
{
	// create the graph given in above fugure
	int V = 13;
	Graph* graph = createGraph(V);
	Allocates(graph);
	/*addEdge(graph, 0, 1);
	addEdge(graph, 0, 4);
	addEdge(graph, 1, 2);
	addEdge(graph, 1, 3);
	addEdge(graph, 1, 4);
	addEdge(graph, 2, 3);
	addEdge(graph, 3, 4);*/

	/*addEdge(graph, 0, 5);
	addEdge(graph, 0, 4);
	addEdge(graph, 1, 2);
	addEdge(graph, 2, 4);
	addEdge(graph, 2, 6);
	addEdge(graph, 3, 7);
	addEdge(graph, 3, 1);
	addEdge(graph, 4, 6);
	addEdge(graph, 4, 2);
	addEdge(graph, 5, 6);
	addEdge(graph, 5, 3);
	addEdge(graph, 7, 4);*/

	/*addEdge(graph, 0, 4);
	addEdge(graph, 4, 2);
	addEdge(graph, 2, 6);
	addEdge(graph, 0, 5);
	addEdge(graph, 5, 3);
	addEdge(graph, 3, 1);
	addEdge(graph, 3, 7);
	addEdge(graph, 1, 2);
	addEdge(graph, 2, 4);
	addEdge(graph, 4, 6);
	addEdge(graph, 5, 6);
	addEdge(graph, 7, 4);*/	

	/*addEdge(graph,0,1);
	addEdge(graph,1,2);
	addEdge(graph,2,0);
	addEdge(graph,2,3);
	addEdge(graph,0,3);*/

	addEdge(graph, 0, 1);
	addEdge(graph, 0, 5);
	addEdge(graph, 0, 6);
	addEdge(graph, 2, 0);
	addEdge(graph, 2, 3);
	addEdge(graph, 3, 5);
	addEdge(graph, 3, 2);
	addEdge(graph, 4, 2);
	addEdge(graph, 4, 3);
	addEdge(graph, 4, 11);
	addEdge(graph, 5, 4);
	addEdge(graph, 6, 4);
	addEdge(graph, 6, 9);
	addEdge(graph, 7, 6);
	addEdge(graph, 7, 8);
	addEdge(graph, 8, 7);
	addEdge(graph, 8, 9);
	addEdge(graph, 9, 10);
	addEdge(graph, 9, 11);
	addEdge(graph, 10, 12);
	addEdge(graph, 11, 12);
	addEdge(graph, 12, 9);

	Sort(graph);

	// print the adjacency list representation of the above graph
	printGraph(graph);

	//StronglyConnectedComponents(graph, V);

	//PathFinder(graph,7,2);
	
	//Metro();
	Free();

	return 0;
}
