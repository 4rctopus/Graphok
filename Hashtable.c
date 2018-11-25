//
// Created by ARCTOPUS on 11/4/2018.
//

/*/
#define HASZNALOM_A_MALLOC_FREE_POINTERET true
#include "debugmalloc/debugmalloc.h"
//*/

#include "Hashtable.h"


const int PRIME1 = 151;

//const int INITIAL_SIZE = 104281;
const int INITIAL_SIZE = 2;


static Hashtable *ht_create_size(void (*f)(void *), int size)
{
    Hashtable *ht = (Hashtable *) malloc(sizeof(Hashtable));
    ht->vector = malloc(size * sizeof(List));
    ht->size = size;
    ht->count = 0;
    ht->free_item = f;
    for(int i = 0; i < ht->size; ++i)
        ht->vector[i] = l_create(free);
    return ht;
}
//*/
Hashtable *ht_create(void (*f)(void *))
{
    return  ht_create_size(f, INITIAL_SIZE);
}
//*/


// ezt a függvényt innen szereztem: https://github.com/jamesroutley/write-a-hash-table
static long long hash_func(const char *key, const int a, const int mod)
{
    long long hash = 0;
    const int len_s = strlen(key);
    for(int i = 0; i < len_s; i++)
    {
        hash += (long long) pow(a, len_s - (i + 1)) * key[i];
        hash = hash % mod;
    }
    return hash;
}

void ht_delete(Hashtable *ht, const char *key)
{
    int hash = hash_func(key, PRIME1, ht->size);

    L_item *it = ht->vector[hash]->front;
    for(; it != NULL; it = it->next)
    {
        if(strcmp(((Ht_item *) it->value)->key, key) == 0)
        {
            /// [TODO] free ht_item allocated memory!!!
            free(((Ht_item *) it->value)->key);
            //free(((Ht_item *) it->value)->value);
            ht->free_item(((Ht_item *) it->value)->value);

            // delete:
            l_delete(ht->vector[hash], it);
            --ht->count;
            break;
        }
    }

    if( ht->count >= ht->size )
        ht_resize(ht, ht->size / 2);

}

void *ht_get(Hashtable *ht, const char *key)
{
    int hash = hash_func(key, PRIME1, ht->size);


    L_item *it = ht->vector[hash]->front;
    for(; it != NULL; it = it->next)
    {
        if(strcmp(((Ht_item *) it->value)->key, key) == 0)
            return ((Ht_item *) it->value)->value;
    }
    return NULL;
}

void ht_insert(Hashtable *ht, const char *key, void *value)
{
    int hash = hash_func(key, PRIME1, ht->size);
    Ht_item *new = malloc(sizeof(Ht_item));
    new->key = malloc(strlen(key) + 1);
    strcpy(new->key, key);
    new->value = value;

    if(ht_get(ht, key) != NULL)
        ht_delete(ht, key);

    l_push_back(ht->vector[hash], new);
    ++ht->count;

    //*/
    if( ht->count >= ht->size )
    {
        ht_resize(ht, ht->size * 2);
    }
    //*/

}

void ht_clear(Hashtable *ht)
{
    Ht_iterator begin = ht_begin(ht);
    while(begin.ht_item != NULL)
    {
        ht_delete(ht, begin.ht_item->key);
        begin = ht_begin(ht);
    }
}

void ht_free(Hashtable *ht)
{
    ht_clear(ht);
    for(int i = 0; i < ht->size; ++i)
        l_free(ht->vector[i]);
    free(ht->vector);
    free(ht);
}

Ht_iterator ht_begin(Hashtable *ht)
{
    Ht_iterator it = {0, NULL, NULL};

    for(int i = 0; i < ht->size; ++i)
        if(!l_is_empty(ht->vector[i]))
        {
            it.bucket = i;
            it.l_item = ht->vector[i]->front;
            it.ht_item = (Ht_item *) it.l_item->value;
            return it;
        }
    return it;
}

Ht_iterator ht_next(Hashtable *ht, Ht_iterator it)
{

    if(it.l_item->next != NULL)
    {
        it.l_item = it.l_item->next;
        it.ht_item = (Ht_item *) it.l_item->value;
        return it;
    }
    if(it.bucket < ht->size - 1)
    {
        ++it.bucket;
        for(int i = it.bucket; i < ht->size; ++i)
            if(!l_is_empty(ht->vector[i]))
            {
                it.bucket = i;
                it.l_item = ht->vector[i]->front;
                it.ht_item = (Ht_item *) it.l_item->value;
                return it;
            }
    }
    it.l_item = NULL;
    it.ht_item = NULL;
    return it;
}
//*/
void ht_resize( Hashtable *ht, int size )
{
    Hashtable *ht_new = ht_create_size(ht->free_item, size);
    for(Ht_iterator it = ht_begin(ht); it.ht_item != NULL; it = ht_next(ht, it))
    {
        ht_insert(ht_new, it.ht_item->key, it.ht_item->value );

        free( it.ht_item->key );
    }


    for( int i = 0; i < ht->size; ++i )
        l_free(ht->vector[i] );

    free( ht->vector );


    ht->count = ht_new->count;
    ht->size = ht_new->size;
    ht->vector = ht_new->vector;

    free( ht_new );

}//*/