//
// Created by xxg20 on 18/02/2022.
//
//
// Part A - supporting file
//

// Graph ADT

#include "Graph.h"
#include <assert.h>
#include <stdlib.h>


//Reference: week 3 lecture a: page 54 graph initialization
Graph newGraph(int V) {
    assert(V >= 0);
    int i;

    Graph g = malloc(sizeof(GraphRep));
    assert(g != NULL);
    g->nV = V;
    g->nE = 0;

    // allocate memory for each row
    g->edges = malloc(V * sizeof(int *));
    assert(g->edges != NULL);
    // allocate memory for each column and initialise with 0
    for (i = 0; i < V; i++) {
        g->edges[i] = calloc(V, sizeof(int));
        assert(g->edges[i] != NULL);
    }

    return g;
}

//Reference: week 3 lecture a: page 55
bool validV(Graph g, Vertex v) {
    return (g != NULL && v >= 0 && v < g->nV);
}

//Reference: week 3 lecture a: page 55
void insertEdge(Graph g, Edge e) {
    assert(g != NULL && validV(g,e.v) && validV(g,e.w));

    if (!g->edges[e.v][e.w]) {  // edge e not in graph
        g->edges[e.v][e.w] = 1;
        g->nE++;
    }
}

//Reference: week 3 programs: Graph.c
void freeGraph(Graph g) {
    assert(g != NULL);

    int i;
    for (i = 0; i < g->nV; i++)
        free(g->edges[i]);
    free(g->edges);
    free(g);
