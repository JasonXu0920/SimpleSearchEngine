//
// Created by xxg20 on 18/02/2022.
//

//
// Part A - supporting file
//


#include <stdbool.h>


// Reference: week 3 lecture a: page 53 Adjacency Matrix Representation
typedef struct GraphRep {
    int  **edges;   // adjacency matrix
    int    nV;      // #vertices
    int    nE;      // #edges
} GraphRep;

//Reference:week 3 lecture a: page 49 Graph ADT interface graph.h
//graph representation is hidden
typedef struct GraphRep *Graph;

// vertices denoted by integers 0--n-1
typedef int Vertex;

// edges are pairs of vertices (end-points)
typedef struct Edge {
    Vertex v;
    Vertex w;
} Edge;

//operations on graphs
Graph newGraph(int); // new graph with V vertices
void  insertEdge(Graph, Edge);
void  freeGraph(Graph);
