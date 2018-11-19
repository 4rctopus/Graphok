//
// Created by ARCTOPUS on 11/1/2018.
//

#ifndef PROGNHF_HASHTABLE_H
#define PROGNHF_HASHTABLE_H

#include <math.h>

#include "List.h"
#include <limits.h>


typedef struct Hashtable
{
    int size;
    int count;
    List **vector;

    void (*free_item)(void *);
} Hashtable;

typedef struct Ht_item
{
    char *key;
    void *value;
} Ht_item;

typedef struct Ht_iterator
{
    int bucket;
    L_item *l_item;
    Ht_item *ht_item;
} Ht_iterator;

Hashtable *ht_create(void (*f)(void *));

void ht_delete(Hashtable *ht, const char *key);

void *ht_get(Hashtable *ht, const char *key);

void ht_insert(Hashtable *ht, const char *key, void *value);

void ht_clear(Hashtable *ht);

void ht_free(Hashtable *ht);

Ht_iterator ht_begin(Hashtable *ht);

Ht_iterator ht_next(Hashtable *ht, Ht_iterator it);


#endif //PROGNHF_HASHTABLE_H
