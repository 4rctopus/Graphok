//
// Created by ARCTOPUS on 11/4/2018.
//

/*/
#define HASZNALOM_A_MALLOC_FREE_POINTERET true
#include "debugmalloc/debugmalloc.h"
//*/

#include "List.h"

List *l_create(void (*f)(void *))
{
    List *list = (List *) malloc(sizeof(List));
    list->front = list->back = NULL;
    list->free_item = f;
    return list;
}

void l_insert_after(List *list, L_item *it, void *var)
{

    L_item *new = (L_item *) malloc(sizeof(L_item));
    new->value = var;

    L_item *next = it->next;

    if(next == NULL)
    {
        list->back = new;
        new->next = NULL;
    }else
    {
        next->prev = new;
        new->next = next;
    }

    it->next = new;
    new->prev = it;

}

void l_insert_before(List *list, L_item *it, void *var)
{
    L_item *new = (L_item *) malloc(sizeof(L_item));
    new->value = var;

    L_item *prev = it->prev;

    if(prev == NULL)
    {
        list->front = new;
        new->prev = NULL;
    }else
    {
        prev->next = new;
        new->prev = prev;
    }

    it->prev = new;
    new->next = it;
}

void l_first(List *list, void *var)
{
    list->front = list->back = (L_item *) malloc(sizeof(L_item));
    list->front->next = list->front->prev = NULL;
    list->front->value = var;
}

void l_push_back(List *list, void *var)
{
    if(l_is_empty(list))
        l_first(list, var);
    else
        l_insert_after(list, list->back, var);
}

void l_push_front(List *list, void *var)
{
    if(l_is_empty(list))
        l_first(list, var);
    else
        l_insert_before(list, list->front, var);
}

void l_delete(List *list, L_item *it)
{
    if(it->prev == NULL && it->next == NULL)
    {
        list->free_item(it->value);

        free(it);
        list->back = list->front = NULL;
        return;
    }


    if(it->next != NULL)
        it->next->prev = it->prev;
    else
        list->back = it->prev;

    if(it->prev != NULL)
        it->prev->next = it->next;
    else
        list->front = it->next;


    list->free_item(it->value);

    free(it);
}

void l_clear(List *list)
{
    while(!l_is_empty(list))
        l_pop_front(list);
}

void l_free(void *listp)
{
    l_clear(listp);
    free(listp);
}

void l_pop_back(List *list)
{
    if(!l_is_empty(list))
        l_delete(list, list->back);
}

void l_pop_front(List *list)
{
    if(!l_is_empty(list))
        l_delete(list, list->front);
}

bool l_is_empty(List *list)
{
    return (list->front == NULL && list->back == NULL);
}
