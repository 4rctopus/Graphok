//
// Created by ARCTOPUS on 11/4/2018.
//

#include "Graph.h"
#include "List.h"


Graph *g_create()
{
    Graph *graph = malloc(sizeof(Graph));
    graph->graph = ht_create(free);
    graph->directed = graph->weighted = true;
    graph->nodes = 0;
    graph->edges = 0;
}

void g_add_node(Graph *graph, const char *nod)
{
    if(ht_get(graph->graph, nod) == NULL)
    {
        List *new_list = l_create(free);
        ht_insert(graph->graph, nod, new_list);

        ++graph->nodes;
    }
}

void g_add_edge(Graph *graph, const char *from, const char *to, int weight)
{
    if(ht_get(graph->graph, from) == NULL)
    {
        List *new_list = l_create(free);
        ht_insert(graph->graph, from, new_list);

        ++graph->nodes;
    }

    if(ht_get(graph->graph, to) == NULL)
    {
        List *new_list = l_create(free);
        ht_insert(graph->graph, to, new_list);

        ++graph->nodes;
    }

    Edge *new_edge = malloc(sizeof(Edge));
    strcpy(new_edge->node, to);
    new_edge->weigth = weight;

    l_push_back(((List *) ht_get(graph->graph, from)), new_edge);
    ++graph->edges;
}

void g_display(Graph *graph)
{
    for(Ht_iterator it = ht_begin(graph->graph); it.ht_item != NULL; it = ht_next(graph->graph, it))
    {
        printf("%s: ", it.ht_item->key);
        for(L_item *it2 = ((List *) it.ht_item->value)->front; it2 != NULL; it2 = it2->next)
            printf("(%s, %d)", ((Edge *) it2->value)->node, ((Edge *) it2->value)->weigth);
        printf("\n");
    }
}

void g_remove_edge(Graph *graph, const char *from, const char *to)
{
    List *from_nod = ht_get(graph->graph, from);
    //List *to_nod = ht_get(graph->graph, to);

    for(L_item *it = from_nod->front; it != NULL; it = it->next)
        if(strcmp(((Edge *) it->value)->node, to) == 0)
        {
            l_delete(from_nod, it);
            break;
        }

    /*/
for( L_item *it = to_nod->front; it != NULL; it = it->next )
    if( strcmp(((Edge*)it->value)->node, from ) == 0 )
    {
        l_delete( to_nod, it );
        break;
    }
//*/
}

void g_remove_node(Graph *graph, const char *nod)
{
    List *from_nod = ht_get(graph->graph, nod);

    ht_delete(graph->graph, nod);

    for(L_item *it = from_nod->front; it != NULL; it = it->next)
    {
        List *to_nod = ht_get(graph->graph, ((Edge *) it->value)->node);
        for(L_item *it2 = to_nod->front; it2 != NULL; it2 = it2->next)
            if(strcmp(((Edge *) it2->value)->node, nod) == 0)
                l_delete(to_nod, it2);
    }
}

static char *copy_string(const char *str)
{
    char *p = malloc(strlen(str) + 1);
    strcpy(p, str);
    return p;
}

static int *copy_int(int x)
{
    int *p = malloc(sizeof(int));
    *p = x;
    return p;
}

void g_bfs(Graph *graph, const char *start)
{
    Hashtable *bfs = ht_create(free);

    List *q = l_create(free);
    l_push_back(q, copy_string(start));
    ht_insert(bfs, start, copy_int(1));


    while(!l_is_empty(q))
    {
        char *nod = copy_string(q->front->value);
        l_pop_front(q);
        for(L_item *it = ((List *) ht_get(graph->graph, nod))->front; it != NULL; it = it->next)
        {
            char *nnod = copy_string(((Edge*)it->value)->node);
            if(ht_get(bfs, nnod) == NULL)
            {
                ht_insert(bfs, nnod, copy_int(*(int *) ht_get(bfs, nod) + 1));

                l_push_back(q, copy_string(nnod));
            }
            free(nnod);
        }
        free(nod);
    }

    for(Ht_iterator it = ht_begin(bfs); it.ht_item != NULL; it = ht_next(bfs, it))
        printf("%s: %d\n", it.ht_item->key, *(int *)it.ht_item->value - 1 );

    ht_free(bfs);
    l_free(q);
}


void g_clear(Graph *graph)
{
    ht_clear(graph->graph);
}

void g_free(Graph *graph)
{
    ht_free(graph->graph);
    free(graph);
}

void g_load(Graph *graph, const char *filename)
{
    FILE* fin = fopen(filename, "r");

    int n, m;
    fscanf(fin, "%d %d", &n, &m );

    for( int i = 0; i < m; ++i )
    {
        char from[51], to[51];
        int w;
        fscanf(fin,"%s %s %d", from, to, &w );

        g_add_edge(graph, from, to, w );
    }

    fclose(fin);
}

void g_dfs(Graph *graph, const char *start)
{

}

