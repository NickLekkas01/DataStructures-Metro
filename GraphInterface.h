#include "GraphTypes.h"

void Traverse(Graph *G, Vertex v, void (*Visit)(Vertex x));
void DepthFirst(Graph *G, void (*Visit)(Vertex x),int start);
void PrintElement(Vertex x);
Edge* newEdge(int endpoint);
Graph* createGraph(int n);
void addEdge(Graph* graph, int src, int endpoint);
void printGraph(Graph* graph);
void Sort(Graph *G);
void SortList(Edge *start);
void swap(Edge *a, Edge *b);
void StronglyConnectedComponents(Graph *G, Vertex v);
void PrintDFS(Graph *G);
void PrintEdges(Graph *G);
void Allocates(Graph *G);
void Free();
void PathFinder(Graph *G,Vertex v,Vertex w);
int PathArray(Graph *G,Vertex v,Vertex w);
void Metro();
Graph *MetroPath(char ***MetroMap,int *counter);
void printGraphUndirected(Graph* graph,char ***MetroMapm,int *counter);
int *BreadthFirst(Graph *G, void (*Visit)(Vertex),int start,int end);
