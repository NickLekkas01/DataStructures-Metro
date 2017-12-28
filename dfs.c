#include "GraphInterface.h"
#include "QueueInterface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int counter=0,counterDFS=0,counterT=0,counterB=0,counterF=0,counterC=0,counterNodes=1,tempcnt;
int *CounterNode;
int *DFS;
int **TreeEdge,**BackEdge,**CrossEdge,**ForwardEdge;
Boolean *CurrentlyVisiting;
int *NumberofNodes;
/* This code is a slightly changed version of the code of Chapter 11
of the book
"Data Structures and Program Design in C" by
R. Kruse, C. L. Tondo and B. Leung */


/*
/* global variable visited */
Boolean visited[MAXVERTEX];

void Allocates(Graph *G)
{
  int v;
  CounterNode=malloc((G->n)*sizeof(int));
  CurrentlyVisiting=malloc((G->n)*sizeof(Boolean));
  NumberofNodes=malloc((G->n)*sizeof(int));
  DFS=malloc((G->n)*sizeof(int));
  TreeEdge=malloc(20*sizeof(int*));
  BackEdge=malloc(20*sizeof(int*));
  CrossEdge=malloc(20*sizeof(int*));
  ForwardEdge=malloc(20*sizeof(int*));
  for(v=0 ; v<20 ; v++)
  {
		TreeEdge[v]=malloc(2*sizeof(int));
		BackEdge[v]=malloc(2*sizeof(int));
		CrossEdge[v]=malloc(2*sizeof(int));
		ForwardEdge[v]=malloc(2*sizeof(int));
  }
}

void Free()
{
	free(CounterNode);
	free(CurrentlyVisiting);
	free(NumberofNodes);
	free(DFS);
	free(TreeEdge);
	free(BackEdge);
	free(CrossEdge);
	free(ForwardEdge);
}
/* Traverse: recursive traversal of a graph
   Pre: v is a vertex of graph G
   Post: The depth first traversal, using function Visit, has been
   completed for v and for all vertices adjacent to v.
   Uses: Traverse recursively, Visit */
void Traverse(Graph *G, Vertex v, void (*Visit)(Vertex x))
{
  int i;
  Vertex w;
  Edge *curedge;

  visited[v]=TRUE;
  Visit(v);
  CounterNode[v]=++counter;
  curedge=G->firstedge[v];      /* curedge is a pointer to the first edge (v,_) of V */
  while (curedge){
    w=curedge->endpoint;        /* w is a successor of v and (v,w) is the current edge */
    if (!visited[w])
	{
		CurrentlyVisiting[w]=TRUE;
		TreeEdge[counterT][0]=v;
		TreeEdge[counterT++][1]=w;
		//printf("Treeedge (%d -> %d) \n",v,w);
	 	Traverse(G, w, Visit);
		
	}
	else
	{
		if(CounterNode[v]<CounterNode[w])
		{
			ForwardEdge[counterF][0]=v;
			ForwardEdge[counterF++][1]=w;
			//printf("Forward (%d -> %d) \n",v,w);
		}
		else
		{
			if (CurrentlyVisiting[w] == TRUE)
			{
				BackEdge[counterB][0]=v;
				BackEdge[counterB++][1]=w;		
				//printf("Backedge (%d -> %d) \n",v,w);
			}
			else 
			{
				CrossEdge[counterC][0]=v;
				CrossEdge[counterC++][1]=w;
				//printf("Crossedge (%d -> %d) \n",v,w);
			}
		}
	}
	CurrentlyVisiting[w]=FALSE;
	curedge=curedge->nextedge;  /*curedge is a pointer to the next edge (v,_) of V */
  }
  NumberofNodes[v]=counterNodes++;
  //NumberofNodes[0]=counterNodes;
}

/* DepthFirst: depth-first traversal of a graph
   Pre: The graph G has been created.
   Post: The function Visit has been performed at each vertex of G in depth-first order
   Uses: Function Traverse produces the recursive depth-first order */
void DepthFirst(Graph *G, void (*Visit)(Vertex x),int start)
{

  Vertex v;

  for (v=0; v < G->n; v++)
  {
    visited[v]=FALSE;
	CurrentlyVisiting[v]=FALSE;
	
  }
  
  for (v=start; v < G->n; v++)
    if (!visited[v]) Traverse(G, v, Visit);
  for (v=0; v < start; v++)
    if (!visited[v]) Traverse(G, v, Visit);
	PrintDFS(G);
	PrintEdges(G);
}

void PrintDFS(Graph *G)
{
   int v;
   printf("DFS:");
   for (v=0; v < counterDFS; v++)
   {
	    tempcnt--;
   		printf("%d ",DFS[v]);
   }
}

void PrintEdges(Graph *G)
{
   int v;
   printf("\nTreeEdges: ");
   for (v=0; v < counterT; v++)
		   printf("(%d -> %d)  ",TreeEdge[v][0],TreeEdge[v][1]);

   printf("\nBackEdges: ");
   for (v=0; v < counterB; v++)
		   printf("(%d -> %d)  ",BackEdge[v][0],BackEdge[v][1]);

   printf("\nCrossEdges: ");
   for (v=0; v < counterC; v++)
		   printf("(%d -> %d)  ",CrossEdge[v][0],CrossEdge[v][1]);

   printf("\nForwardEdges: ");
   for (v=0; v < counterF; v++)
		   printf("(%d -> %d)  ",ForwardEdge[v][0],ForwardEdge[v][1]);
}

/* PrintElement: prints the value of its parameter x */
void PrintElement(Vertex x)
{
  
  DFS[counterDFS++]=x; 
  //printf("%d\n", x);
}

// A utility function to create a new adjacency list node
Edge* newEdge(int endpoint)
{
	Edge* newNode =
			(Edge*) malloc(sizeof(Edge));
	newNode->endpoint = endpoint;
	newNode->nextedge = NULL;
	return newNode;
}

// A utility function that creates a graph of V vertices
Graph* createGraph(int n)
{
	Graph* graph = (Graph*) malloc(sizeof(Graph));
	graph->n = n;

	// Initialize each adjacency list as empty by making head as NULL
	int i;
	for (i = 0; i < n; ++i)
		graph->firstedge[i] = NULL;
	return graph;
}

// Adds an edge to an undirected graph
void addEdge(Graph* graph, int src, int endpoint)
{
	// Add an edge from src to dest. A new node is added to the adjacency
	// list of src. The node is added at the begining
	Edge* newNode = newEdge(endpoint);
	Edge* temp = graph->firstedge[src];
	
	newNode->nextedge = graph->firstedge[src];
	graph->firstedge[src] = newNode;

}

// A utility function to print the adjacenncy list representation of graph
void printGraph(Graph* graph)
{
	int v;
	for (v = 0; v < graph->n; ++v)
	{
		Edge* pCrawl = graph->firstedge[v];
		printf("\n Adjacency list of vertex %d\n head ", v);
		while (pCrawl)
		{
			printf("-> %d", pCrawl->endpoint);
			pCrawl = pCrawl->nextedge;
		}
		printf("\n");
	}
}

void Sort(Graph *G)
{
	int i;
	for ( i=0 ; i<G->n ; i++ )
		SortList(G->firstedge[i]);
}

/* Bubble sort the given linked lsit */
void SortList(Edge *start)
{
    int swapped, i;
    Edge *ptr1;
    Edge *lptr = NULL;
	ptr1 = start;
    /* Checking for empty list */
    if (ptr1 == NULL)
        return;
 
    do
    {
        swapped = 0;
        ptr1 = start;
 
        while (ptr1->nextedge != lptr)
        {
            if (ptr1->endpoint > ptr1->nextedge->endpoint)
            { 
                swap(ptr1, ptr1->nextedge);
                swapped = 1;
            }
            ptr1 = ptr1->nextedge;
        }
        lptr = ptr1;
    }
    while (swapped);
}
 
/* function to swap data of two nodes a and b*/
void swap(Edge *a, Edge *b)
{
    int temp = a->endpoint;
    a->endpoint = b->endpoint;
    b->endpoint = temp;
}

void StronglyConnectedComponents(Graph *G, Vertex v)
{
	int w;
	Graph* graph2=createGraph(v);

	/*DFS*/
	DepthFirst(G,PrintElement,0);
	
	/*Add edges reversed*/
	for(v=0 ; v<counterT ; v++)
		addEdge(graph2,TreeEdge[v][1],TreeEdge[v][0]);
	for(v=0 ; v<counterB ; v++)
		addEdge(graph2,BackEdge[v][1],BackEdge[v][0]);
	for(v=0 ; v<counterC ; v++)
		addEdge(graph2,CrossEdge[v][1],CrossEdge[v][0]);
	for(v=0 ; v<counterF ; v++)
		addEdge(graph2,ForwardEdge[v][1],ForwardEdge[v][0]);
		
		/*Find the maxplace*/
		int *maxplace,max;
		int a=0;
		maxplace=malloc(counterNodes*sizeof(int));
		counterNodes--;
		for(v=counterNodes ; v>=0 ; v--)
		{
			for(w=0 ; w<G->n ; w++)
				if(NumberofNodes[w]==v)
				{
					maxplace[a++]=w;
					break;
				}
		}	
		
		/*Print Graph*/
		printGraph(graph2);
		
		printf("\n");
		a=0;
		for (v=0; v < graph2->n; v++)
 	 	{
    		visited[v]=FALSE;
			CurrentlyVisiting[v]=FALSE;
	
  		}
		do
		{
			tempcnt=NumberofNodes[maxplace[a]];
			counter=0;counterDFS=0;
   	 		if (!visited[maxplace[a]])
			{
				Traverse(graph2, maxplace[a], PrintElement);
				printf("Strongly Connected Components ");
				PrintDFS(graph2);
				printf("\n");
			}
			a++;
		}
		while(tempcnt>1);
}

int countPath=0;
int *Path;

void PathFinder(Graph *G,Vertex v,Vertex w)
{
	
	int i,tmp;
	DepthFirst(G,PrintElement,v);
	Path=malloc((G->n)*sizeof(int));
	for(i=0 ; i<counterT ; i++)
		if(TreeEdge[i][0]==v)
			tmp=i;
	Path[countPath++]=TreeEdge[tmp][0];
	tmp=PathArray(G,v,w);
	if(tmp!=-1)
	{
		Path[countPath++]=w;
		printf("\nPath: ");
		for(i=0 ; i<countPath ; i++)
		{
			printf(" %d  ",Path[i]);
		}
	}
}

int PathArray(Graph *G,Vertex v,Vertex w)
{
	int i,flag=0;
	for(i=0 ; i<counterT ; i++)
		if(TreeEdge[i][0]==v)
		{
			v=i;
			flag=1;
			break;
		}
	if(flag==0)
	{
		printf("\nThere is no path \n");
		return -1;
	}
	if(TreeEdge[v][1] != w)
	{
		Path[countPath++]=TreeEdge[v][1];
		PathArray(G,TreeEdge[v][1],w);
	}
	
}


void Metro()
{
	FILE *fp = fopen ( "Metro.txt", "r");
    char line[1024];
    char ch = getc ( fp );
    int index = 0;
	int MetroLine=0;
	int counter[3];
	int i,j;
	for(i=0 ; i<3 ; i++)
		counter[i]=0;
    while ( ch != EOF ) {
        if ( ch != '\n'){
            line[index++] = ch;
			if(ch=='-')
				counter[MetroLine]++;
        }else
		{
			counter[MetroLine]++;
            line[index++] = '-';
			MetroLine++;
		}
        ch = getc ( fp );
	}
	line[index++] = '\0';
	counter[MetroLine]++;
	index=0;
	char ***MetroMap;
	MetroMap=malloc(3*sizeof(char**));
	for(i=0 ; i<3 ; i++)
	{
		MetroMap[i]=malloc(50*sizeof(char*));
		for(j=0 ; j<50 ; j++)
		{
			MetroMap[i][j]=malloc(100*sizeof(char));
		}
	}
		
	
	const char s[2] = "-";
	char *token;
	MetroLine=0;
   /* get the first token */
   token = strtok(line, s);
   
   /* walk through other tokens */
   while( token != NULL ) 
   {
	  strcpy(MetroMap[MetroLine][index],token);
	  //char one[10];
	  //snprintf(one,sizeof(one),"(%d)",MetroLine+1);
	  //strcat(MetroMap[MetroLine][index],one);
      token = strtok(NULL, s);
	  index++;
	  if (index==counter[MetroLine])
	  {
		index=0;
	  	MetroLine++;
		//printf("\nSTOP\n");
	  }
	  
   }
 //printf ( "%s\n", line );
 	for(i=0 ; i<3 ; i++)
	 {
	 	for(j=0 ; j <counter[i]; j++)
		 	printf("%s ",MetroMap[i][j]);
		printf("\n");
	 }

	 Graph *graph=MetroPath(MetroMap,counter);
}


Graph *MetroPath(char ***MetroMap,int *counter)
{
	Graph* graph=createGraph((counter[0]+counter[1]+counter[2]));
	int i,j,k;
	for(j=0 ; j<counter[0]-1 ; j++)
	{
		addEdge(graph,j+1,j);
		addEdge(graph,j,j+1);
	}
	for(j=0 ; j<counter[1]-1 ; j++)
	{
		addEdge(graph,counter[0]+j+1,counter[0]+j);
		addEdge(graph,counter[0]+j,counter[0]+j+1);
	}
	for(j=0 ; j<counter[2]-1 ; j++)
	{
		addEdge(graph,counter[0]+counter[1]+j+1,counter[0]+counter[1]+j);
		addEdge(graph,counter[0]+counter[1]+j,counter[0]+counter[1]+j+1);
	}
	for(i=0 ; i<counter[0] ; i++)
	{
			for(j=0 ; j<counter[1] ; j++)
			{
				if(strcmp(MetroMap[0][i],MetroMap[1][j])==0)
				{
					addEdge(graph,i,counter[0]+j);
					addEdge(graph,counter[0]+j,i);
				}
			}
	}
	for(i=0 ; i<counter[0] ; i++)
	{
			for(j=0 ; j<counter[2] ; j++)
			{
				if(strcmp(MetroMap[0][i],MetroMap[2][j])==0)
				{
					addEdge(graph,i,counter[0]+counter[1]+j);
					addEdge(graph,counter[0]+counter[1]+j,i);
				}
			}
	}
	for(i=0 ; i<counter[1] ; i++)
	{
			for(j=0 ; j<counter[2] ; j++)
			{
				if(strcmp(MetroMap[1][i],MetroMap[2][j])==0)
				{
					addEdge(graph,counter[0]+i,counter[0]+counter[1]+j);
					addEdge(graph,counter[0]+counter[1]+j,counter[0]+i);
				}
			}
	}		
	printGraphUndirected(graph,MetroMap,counter);
	
	int start=25,end=13;
	int *Path=BreadthFirst(graph,PrintElement,start,end);
	printf("Path: ");
	for(i=countPath-1 ; i>=0 ; i--)
	{
				if(Path[i]<counter[0])
					printf("%s (1)  ",MetroMap[0][Path[i]]);
				else if(Path[i]<counter[0]+counter[1])
					printf("%s (2)  ", MetroMap[1][(Path[i])-counter[0]]);
				else
					printf("%s (3)  ", MetroMap[2][(Path[i])-counter[0]-counter[1]]);
	}
	return graph;
} 

// A utility function to print the adjacenncy list representation of graph
void printGraphUndirected(Graph* graph,char ***MetroMap,int *counter)
{
	int v,i;
	int *visiting;
	visiting=malloc((graph->n)*sizeof(int));
	for (v = 0; v < graph->n; ++v)
		visiting[v]=0;
	printf("COUNTER %d %d %d graph %d",counter[0],counter[1],counter[2],graph->n);
	for (v = 0; v < graph->n; ++v)
	{
		Edge* pCrawl = graph->firstedge[v];
		if(v<counter[0])
					//printf("-> %d", pCrawl->endpoint);
				printf("\n Adjacency list of vertex %s (1)\n head ", MetroMap[0][v]);
		else if(v<counter[0]+counter[1])
				printf("\n Adjacency list of vertex %s (2)\n head ", MetroMap[1][(v)-counter[0]]);
		else
				printf("\n Adjacency list of vertex %s (3)\n head ", MetroMap[2][(v)-counter[0]-counter[1]]);
		
		while (pCrawl)
		{
			
			if(visiting[pCrawl->endpoint]==0)
			{
				if(pCrawl->endpoint<counter[0])
					//printf("-> %d", pCrawl->endpoint);
					printf("-> %s (1)",MetroMap[0][pCrawl->endpoint]);
				else if(pCrawl->endpoint<counter[0]+counter[1])
					printf("-> %s (2)", MetroMap[1][(pCrawl->endpoint)-counter[0]]);
				else
					printf("-> %s (3)", MetroMap[2][(pCrawl->endpoint)-counter[0]-counter[1]]);
				visiting[pCrawl->endpoint]=1;
				//break;
				pCrawl = pCrawl->nextedge;
			}
		
			
		}
		printf("\n");
		for (i = 0; i < graph->n; ++i)
			visiting[i]=0;
		//v=v+counter[a++];
	}
}