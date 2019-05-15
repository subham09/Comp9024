// written by Subham Anand

#include <stdbool.h>


typedef struct GraphRep *Graph;

typedef int Vertex;

typedef struct GraphRep{
	
	int **edges;
	int nV;
	int nE;
	
}GraphRep;

typedef struct Edge {
   Vertex v;
   Vertex w;
} Edge;

Graph newGraph(int);
void  insertEdge(Graph, Edge);
void  removeEdge(Graph, Edge);
bool  adjacent(Graph, Vertex, Vertex);
void  showGraph(Graph);
void  freeGraph(Graph);


