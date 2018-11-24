//
// Created by ARCTOPUS on 11/24/2018.
//

#include <malloc.h>
#include <stdio.h>

//*/
//#define HASZNALOM_A_MALLOC_FREE_POINTERET true
#include "debugmalloc/debugmalloc.h"
//*/


#include "Heap.h"

int compar( void *a, void *b )
{
    int s1 = *(int*)a;
    int s2 = *(int*)b;

    return s1 - s2;
}

static int *copy_int(int x)
{
    int *p = malloc(sizeof(int));
    *p = x;
    return p;
}

int main()
{
    Heap *heap = h_create( 1000, compar );

    int v[15] = { 2, 3, 5, 1, 2, 4, 9, 333, 41, -3 };


    for( int i = 0; i < 10; ++i )
        h_push(heap, copy_int(v[i]) );

//*/
    while( heap->size > 0 )
    {
        int x = *(int*)h_getmin(heap);
        h_pop(heap);

        printf( "%d\n", x );
    }
    //*/

    h_free(heap);

    debugmalloc_dump();
}
