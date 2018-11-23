#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

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

    char inp[51] = "";
    while(strcmp(inp, "exit") != 0)
    {
        scanf("%s", inp);
        if(strcmp(inp, "add_edge") == 0)
        {
            char from[51], to[51];
            int w = 1;
            if( graph->weighted )
                scanf("%s %s %d", from, to, &w);
            else
                scanf("%s %s", from, to);

            g_add_edge(graph, from, to, w);
            if( !graph->directed )
                g_add_edge(graph, to, from, w);
        }else if(strcmp(inp, "display") == 0)
        {
            g_display(graph);
        }else if(strcmp(inp, "remove_edge") == 0)
        {
            char from[51], to[51];
            scanf("%s %s", from, to);
            g_remove_edge(graph, from, to);
        }else if(strcmp(inp, "remove_node") == 0)
        {
            char nod[51];
            scanf("%s", nod);
            g_remove_node(graph, nod);
        }
        else if( strcmp(inp, "add_node") == 0 )
        {
            char nod[51];
            scanf("%s", nod );
            g_add_node(graph, nod );
        }
        else if( strcmp(inp, "bfs" ) == 0 )
        {
            char nod[51];
            scanf("%s", nod );
            g_bfs(graph, nod );
        }
        else if( strcmp( inp, "dfs" ) == 0 )
        {
            char nod[51];
            scanf("%s", nod );
            g_dfs(graph, nod );
        }
        else if( strcmp( inp, "load" ) == 0 )
        {
            char file[51];
            scanf("%s", file );
            g_load(graph, file);
        }
        else if( strcmp(inp, "+w") == 0 )
            graph->weighted = true;
        else if( strcmp(inp, "-w") == 0 )
            graph->weighted = false;
        else if( strcmp(inp, "+d") == 0 )
            graph->directed = true;
        else if( strcmp(inp, "-d") == 0 )
            graph->directed = false;
        else if( strcmp(inp, "prop") == 0 )
            g_display_properties(graph);

    }

    g_free(graph);

    //debugmalloc_dump();

    return 0;
}
