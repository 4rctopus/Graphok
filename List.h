//
// Created by ARCTOPUS on 11/1/2018.
//

#ifndef LIST_H
#define LIST_H

#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct L_item
{
    void *value;
    struct L_item *next, *prev;
} L_item;

typedef struct List
{
    void (*free_item)(void *);

    struct L_item *front, *back;
} List;


List *l_create(void (*f)(void *));

void l_insert_after(List *list, L_item *it, void *var);

void l_insert_before(List *list, L_item *it, void *var);

bool l_is_empty(List *list);

void l_first(List *list, void *var);

void l_push_back(List *list, void *var);

void l_push_front(List *list, void *var);

void l_delete(List *list, L_item *it);

void l_pop_front(List *list);

void l_pop_back(List *list);

void l_clear(List *list);

void l_free(void *list);

#endif //PROGNHF_LIST_H
