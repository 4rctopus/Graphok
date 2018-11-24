//
// Created by ARCTOPUS on 11/24/2018.
//


#include <malloc.h>

//*/
#define HASZNALOM_A_MALLOC_FREE_POINTERET true
#include "debugmalloc/debugmalloc.h"
//*/

#include <stdio.h>

#include "Heap.h"




static int parent(int i){return (i - 1) / 2;}
static int left(int i){ return (2 * i + 1);}
static int right(int i){ return (2 * i + 2);}

void swap( void **x, void **y )
{
    void *emp = *x;
    *x = *y;
    *y = emp;
}

void h_push(Heap *heap, void *item )
{
    if(heap->size == heap->capacity)
        return;

    int i = heap->size;
    ++heap->size;


    heap->vector[i] = item;
    while( i != 0 && heap->compare( heap->vector[i], heap->vector[parent(i)] ) < 0 )
    {
        swap( &heap->vector[i], &heap->vector[parent(i)] );
        i = parent(i);
    }
}

static int min_child( Heap* heap, int i )
{
    if( right(i) > heap->size )
        return left(i);
    else
    {
        if( heap->compare(heap->vector[left(i)] , heap->vector[right(i)] ) < 0 )
            return left(i);
        else
            return right(i);
    }
}

void h_pop(Heap *heap)
{
    if( heap->size == 0 )
        return;

    free( heap->vector[0] );
    --heap->size;
    heap->vector[0] = heap->vector[heap->size];


    int i = 0;
    while( left(i) < heap->size )
    {
        int mc = min_child(heap, i);
        if( heap->compare(heap->vector[i], heap->vector[mc] ) > 0  )
            swap( &heap->vector[i], &heap->vector[mc]);
        i = mc;
    }
}

void *h_getmin(Heap *heap)
{
    if( heap->size == 0 )
        return  NULL;
    return heap->vector[0];
}

Heap *h_create(int capacity, int (*compare)(void *, void *))
{
    Heap *heap = malloc(sizeof(Heap));
    heap->capacity = capacity;
    heap->compare = compare;
    heap->vector = malloc(sizeof(void*) * capacity);

    heap->size = 0;

    return heap;
}

void h_clear( Heap *heap )
{
    for( int i = 0; i < heap->size; ++i )
        free( heap->vector[i] );
    heap->size = 0;
}

void h_free( Heap *heap )
{
    h_clear(heap);
    free( heap->vector );
    free( heap );
}
