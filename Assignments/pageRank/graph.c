//written by Subham Anand
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "graph.h"

//typedef struct GraphRep{
//	
//	int **edges;
//	int nV;
//	int nE;
//	
//}GraphRep;

Graph newGraph(int V){
	
	assert(V>=0);
	Graph g = malloc(sizeof(GraphRep));
	g->nE = 0;
	g->nV = V;
	int i = 0;
	
	g->edges = malloc(V * sizeof(int *));
	assert(g->edges != NULL);
	
	for (i = 0; i < V ; i++)
	{
		g->edges[i] = calloc(V, sizeof(int));
		assert(g->edges[i] != NULL); 
	}
	
	return g;
}

bool validV(Graph g, Vertex v){
	
	if (g != NULL && v >= 0 && v < g->nV)
	{
		return true;
	}
	return false;
}

void insertEdge(Graph g, Edge e){
	assert(g != NULL && validV(g,e.v) && validV(g, e.w));
	
	if (g->edges[e.v][e.w] == 0)
	{
		g->edges[e.v][e.w] = 1;
	//	g->edges[e.w][e.v] = 1;
		g->nE++;
	}
}

void removeEdge(Graph g, Edge e) {
	assert(g != NULL && validV(g,e.v) && validV(g, e.w));
	
	if (g->edges[e.v][e.w])
	{
		g->edges[e.v][e.w] = 0;
		//g->edges[e.w][e.v] = 0;
		g->nE--;
	}
	
}

bool adjacent(Graph g, Vertex v, Vertex w) {
	assert(g != NULL && validV(g,v) && validV(g, w));
	
	if (g->edges[v][w] != 0)
	{
		return true;
	}
	return false;
}

void showGraph(Graph g) {
    assert(g != NULL);
    int i= 0, j = 0;

    printf("vertices: %d\n", g->nV);
    printf("edges: %d\n", g->nE);
    for (i = 0; i < g->nV; i++)
    {
    	for (j = 0; j < g->nV; j++)
    	{
    		if (g->edges[i][j])
    		{
    			printf("Edge %d - %d\n", i, j);
			} 
		}
	}
}
       
void freeGraph(Graph g) {
   assert(g != NULL);

   int i;
   for (i = 0; i < g->nV; i++)
   {
   	   free(g->edges[i]);	
   }
   free(g->edges);
   free(g);
}


//int main(int argc, char *argv[])
//{
//	Graph a = newGraph(5);
//	Vertex x = 1;
//	Vertex y = 2;
//	//printf("%d\n",validV(a, 6));
//	Edge e1;
//	e1.v = 1;
//	e1.w = 2;
//	insertEdge(a, e1);
//	printf("edge added %d\n",a->nE);
//	showGraph(a);
//	printf("%d\n",adjacent(a,x,y));
//	//removeEdge(a, e1);
//	//printf("%d\n",a->nE);
//	return 0;
//}
