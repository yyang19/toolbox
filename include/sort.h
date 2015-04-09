#ifndef _HEADER_SORT_
#define _HEADER_SORT_

#include <stdbool.h>

typedef struct node{
    int key;
    struct node *next;
}node_t;


void quicksort( int *array, int start, int end, bool recursive );
void quicksort_ll(node_t **headRef);
void quicksort_ll_push( node_t ** head_ref, int new_key );
void  quicksort_ll_dump( node_t *head );
#endif
