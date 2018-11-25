#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#include "List.h"
#include "Hashtable.h"
#include "Graph.h"

/*/
#define HASZNALOM_A_MALLOC_FREE_POINTERET true
#include "debugmalloc/debugmalloc.h"
//*/


int main()
{
    Graph *graph = g_create();

    char inp[NODE_LENGTH] = "";
    while(strcmp(inp, "exit") != 0)
    {
        scanf("%s", inp);
        if(strcmp(inp, "add_edge") == 0)
        {
            char from[NODE_LENGTH], to[NODE_LENGTH];
            int w = 1;
            if(graph->weighted)
                scanf("%s %s %d", from, to, &w);
            else
                scanf("%s %s", from, to);

            g_add_edge(graph, from, to, w);
            if(!graph->directed)
                g_add_edge(graph, to, from, w);
        }
        else if(strcmp(inp, "display") == 0)
        {
            g_display(graph);
        }
        else if(strcmp(inp, "remove_edge") == 0)
        {
            char from[NODE_LENGTH], to[NODE_LENGTH];
            scanf("%s %s", from, to);
            g_remove_edge(graph, from, to);
        }
        else if(strcmp(inp, "remove_node") == 0)
        {
            char nod[NODE_LENGTH];
            scanf("%s", nod);
            g_remove_node(graph, nod);
        }
        else if(strcmp(inp, "add_node") == 0)
        {
            char nod[NODE_LENGTH];
            scanf("%s", nod);
            g_add_node(graph, nod);
        }
        else if(strcmp(inp, "bfs") == 0)
        {
            char nod[NODE_LENGTH];
            scanf("%s", nod);
            g_bfs(graph, nod);
        }
        else if(strcmp(inp, "dfs") == 0)
        {
            char nod[NODE_LENGTH];
            scanf("%s", nod);
            g_dfs(graph, nod);
        }
        else if( strcmp(inp, "bell") == 0 )
        {
            char nod[NODE_LENGTH];
            scanf("%s", nod);
            g_bellman_ford(graph, nod);
        }
        else if( strcmp( inp, "dijk") == 0 )
        {
            char nod[NODE_LENGTH];
            scanf("%s", nod);
            g_dijkstra(graph, nod);
        }
        else if( strcmp( inp, "mst") == 0 )
        {
            char minmax[NODE_LENGTH];
            scanf("%s", minmax);
            g_mst(graph, minmax);
        }
        else if(strcmp(inp, "load") == 0)
        {
            char file[NODE_LENGTH];
            scanf("%s", file);

            printf("Do you wish to proceed, if you do, your current graph will be lost? (Y/N)\n");
            char yn = '0';
            while(tolower(yn) != 'y' && tolower(yn) != 'n')
            {
                scanf("%c", &yn);
                if(tolower(yn) == 'y')
                {
                    if( g_load(graph, file) )
                        printf("Loaded graph from '%s'\n", file);
                    else
                        printf("Failed to load graph from '%s'\n", file );
                }
            }
        }
        else if( strcmp(inp, "save") == 0 )
        {
            char file[NODE_LENGTH];
            scanf("%s", file);

            if( g_save(graph, file) )
                printf("Saved graph to '%s'\n", file);
            else
                printf("Failed to save graph to '%s'\n", file );
        }
        else if(strcmp(inp, "+w") == 0)
            graph->weighted = true;
        else if(strcmp(inp, "-w") == 0)
            graph->weighted = false;
        else if(strcmp(inp, "+d") == 0)
            graph->directed = true;
        else if(strcmp(inp, "-d") == 0)
            graph->directed = false;
        else if(strcmp(inp, "prop") == 0)
            g_display_properties(graph);
        else if(strcmp(inp, "exit") != 0)
            printf("\'%s\' is not recognized as a command.\n", inp);

    }

    g_free(graph);

    //debugmalloc_dump();

    return 0;
}
