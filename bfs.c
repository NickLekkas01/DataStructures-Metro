#include <stdio.h>
#include <stdlib.h>
#include "QueueInterface.h"
#include "GraphTypes.h"

/* This code is a slightly changed version of the code of Chapter 11
of the book
"Data Structures and Program Design in C" by
R. Kruse, C. L. Tondo and B. Leung */


/* PrintElement: prints the value of its parameter x */
/*void PrintElement(Vertex x)
{
  printf("%d\n", x);
}*/


/* BreadthFirst: breadth-first traversal of a graph
   Pre: The graph G has been created
   Post: The function visit has been performed at each vertex of G, where the vertices
   are chosen in breadth-first order.
   Uses: Queue functions */

int *BreadthFirst(Graph *G, void (*Visit)(Vertex),int start,int end)
{
  Queue Q;
  Boolean visited[MAXVERTEX];
  Vertex v, w,*Prev,*Path,cnt=0;
  Prev=malloc((G->n)*sizeof(int));
  Edge *curedge;
  for (v=0; v < G->n; v++)
    visited[v]=FALSE;

  InitializeQueue(&Q);
  Insert(start, &Q);
  //visited[start]=FALSE;
      do {
         Remove(&Q, &v);
         
         if (!visited[v]){
           visited[v]=TRUE;
           Visit(v);
         }
    
         curedge=G->firstedge[v];  /* curedge is a pointer to the first edge (v,_) of V */
         while (curedge){
            w=curedge->endpoint;  /* w is a successor of v and (v,w) is the current edge */
            if (!visited[w]) Prev[w]=v;
            if(w==end) break;
            if (!visited[w]) Insert(w, &Q);
            curedge=curedge->nextedge;  /*curedge is a pointer to the next edge (v,_) of V */
         }
         if(w==end) break;
      } while (!Empty(&Q) );
      
      if(w==end)
      {
        Path=malloc((G->n)*sizeof(int));
        Path[0]=w;
        while(w!=start)
        {
          cnt++;
          Path[cnt]=Prev[w];
          w=Prev[w];
        }
      countPath=cnt;
      return Path;
      }
}

