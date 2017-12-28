/* This code is a slightly changed version of the code of Chapter 11
of the book
"Data Structures and Program Design in C" by
R. Kruse, C. L. Tondo and B. Leung */


/* BreadthTopSort: generates breadth-first topological ordering
   Pre: G is a directed graph with no cycles implemented with a contiguous list of vertices and linked adjacency lists.
   Post: The function makes a breadth-first traversal of G and generates the resulting topological order in T
   Uses: Queue functions */

void BreadthTopSort(Graph G, Toporder T)
{
  
  int predecessorcount[MAXVERTEX];    /* number of predecessors of each vertex */
  
  Queue Q;
  Vertex v, succ;
  Edge *curedge;
  int place;

  /* initialize all the predecessor counts to 0  */
  for (v=0; v < G.n; v++)
    predecessorcount[v]=0;
    
  /* increase the predecessor count for each vertex that is a successor of another one */
  for (v=0; v < G.n; v++)
    for (curedge=G.firstedge[v]; curedge; curedge=curedge->nextedge)
       predecessorcount[curedge->endpoint]++;
  
  /* initialize a queue */
  InitializeQueue(&Q);

  /* place all vertices with no predecessors into the queue */
  for (v=0; v < G.n; v++)
    if (predecessorcount[v]==0)
      Insert(v, &Q);
  
  /* start the breadth-first traversal */
  place=-1;
  while (!Empty(&Q)) {
    /* visit v by placing it into the topological order */
    Remove(&Q, &v);
    place++;
    T[place]=v;
    
    /* traverse the list of successors of v */
    for (curedge=G.firstedge[v]; curedge; curedge=curedge->nextedge){
       /* reduce the predecessor count for each successor */
       succ=curedge->endpoint;
       predecessorcount[succ]--;
       if (predecessorcount[succ]==0)
         /* succ has no further predecessors, so it is ready to process */
         Insert(succ, &Q);
    }
  }
}
  


