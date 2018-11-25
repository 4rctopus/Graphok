#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "List.h"
#include "Hashtable.h"


int *copy_int(int x)
{
    int *p = malloc(sizeof(int));
    *p = x;
    return p;
}

char *copy_string(const char *str)
{
    char *p = malloc(strlen(str) + 1);
    strcpy(p, str);
    return p;
}


int main()
{
    Hashtable *graph = ht_create(l_free);
    int n, m;
    char start[51];
    Hashtable *bfs = ht_create(free);

    scanf(" %d %d %s", &n, &m, start);

    for(int i = 0; i < m; ++i)
    {
        char x[51], y[51];
        scanf(" %s %s ", x, y);

        if(ht_get(graph, x) == NULL)
        {
            List *new_list = l_create(free);
            ht_insert(graph, x, new_list);
        }


        if(ht_get(graph, y) == NULL)
        {
            List *new_list = l_create(free);
            ht_insert(graph, y, new_list);
        }


        l_push_back(((List *) ht_get(graph, x)), copy_string(y));
    }


    List *q = l_create(free);
    l_push_back(q, copy_string(start));
    ht_insert(bfs, start, copy_int(1));


    while(!l_is_empty(q))
    {
        char *nod = copy_string(q->front->value);
        l_pop_front(q);
        for(L_item *it = ((List *) ht_get(graph, nod))->front; it != NULL; it = it->next)
        {
            char *nnod = it->value;
            if(ht_get(bfs, nnod) == NULL)
            {
                ht_insert(bfs, nnod, copy_int(*(int *) ht_get(bfs, nod) + 1));

                l_push_back(q, copy_string(nnod));
            }
        }
        free(nod);
    }


    int *dist = malloc(sizeof(int) * (n + 2));
    for(int i = 1; i <= n; ++i)
        dist[i] = -1;


    for(Ht_iterator it = ht_begin(bfs); it.ht_item != NULL; it = ht_next(bfs, it))
    {
        int idx;
        sscanf(it.ht_item->key, "%d", &idx);
        dist[idx] = *(int *) it.ht_item->value - 1;
    }

    for(int i = 1; i <= n; ++i)
        printf("%d ", dist[i]);


    free(dist);
    ht_free(graph);
    ht_free(bfs);
    l_free(q);
    return 0;
}
