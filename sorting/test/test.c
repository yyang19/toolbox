#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include <random.h>
#include "sort.h"

#define MAX (8192)

static void
_help( void ){

}


static void 
shuffle_array( int *a, int ub )
{
    int i,j;
    int temp;

    for( i=ub-1; i>0; i-- ){
        j = random_in_range(0, i+1);
        temp = a[i];
        a[i]=a[j];
        a[j]=temp;
    }

}

static void
create_array( int *a, int n, int max ){
    
    int in, im;

    im = 0;

    for (in = 0; in < max && im < n; ++in) {
        int rn = max - in;
        int rm = n - im;
        if ( random_in_range( 1,max ) % rn < rm)    
            /* Take it */
            a[im++] = in + 1; /* +1 since your range begins from 1 */
    }

    assert(im == n);

    shuffle_array( a, n );
}

static void
reset_array( int *a, int len )
{
    int i;

    for( i=0; i<len; i++ )
        a[i]=-1;
}


int 
main( int argc, char *argv[] ){
    
    int i;
    int result=0;
    int keys[MAX];
    int copy[MAX];
    node_t *a = NULL;
    
    if( 0 )
        _help();

    create_array( &keys[0], MAX, MAX );

    for(i=0; i<MAX; i++)
        copy[i]=keys[i];

    quicksort( &keys[0], 0, MAX-1, 1 );
    quicksort( &copy[0], 0, MAX-1, 0 );

    reset_array( &keys[0], MAX );
    reset_array( &copy[0], MAX );
    
    printf("Test quicksort on singly list\n");
    
    quicksort_ll_push(&a, 5);
    quicksort_ll_push(&a, 20);
    quicksort_ll_push(&a, 4);
    quicksort_ll_push(&a, 3);
    quicksort_ll_push(&a, 30);

    printf( "Linked List before sorting \n" );;
    quicksort_ll_dump(a);

    quicksort_ll(&a);

    printf( "Linked List after sorting \n" );
    quicksort_ll_dump(a);
    return result;
}
