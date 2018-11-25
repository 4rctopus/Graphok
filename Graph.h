//
// Created by ARCTOPUS on 11/3/2018.
//

#ifndef PROGNHF_GRAPH_H
#define PROGNHF_GRAPH_H

#include "Hashtable.h"

#define NODE_LENGTH 51

typedef struct Edge
{
    char node[NODE_LENGTH];
    int weigth;
} Edge;

typedef struct Graph
{
    Hashtable *graph;
    int nodes, edges;
    bool directed;
    bool weighted;
} Graph;

Graph *g_create();

void g_add_node(Graph *graph, const char *nod);
void g_add_edge(Graph *graph, const char *from, const char *to, int weight);
void g_remove_node(Graph *graph, const char *nod);
void g_remove_edge(Graph *graph, const char *from, const char *to);

void g_display(Graph *graph);
void g_display_properties(Graph *graph);

void g_bfs(Graph *graph, const char *start);
void g_dfs(Graph *graph, const char *start);
void g_bellman_ford(Graph *graph, const char *start);
void g_dijkstra(Graph *graph, const char *start);
void g_mst(Graph *graph, const char *minmax);

void g_clear(Graph *graph);
void g_free(Graph *graph);

bool g_load(Graph *graph, const char *filename);
bool g_save(Graph *graph, const char *filename);


#endif //PROGNHF_GRAPH_H
