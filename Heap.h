//
// Created by ARCTOPUS on 11/24/2018.
//

#ifndef PROGNHF_HEAP_H
#define PROGNHF_HEAP_H

#endif //PROGNHF_HEAP_H


typedef struct Heap
{
    int size;
    int capacity;
    int (*compare)(void *, void *);
    void **vector;
} Heap;


Heap *h_create( int capacity, int (*compare)(void *, void *));

void h_push(Heap *heap, void *item);
void h_pop(Heap *heap);
void *h_getmin(Heap *heap);

void h_clear( Heap *heap );
void h_free( Heap *heap );
