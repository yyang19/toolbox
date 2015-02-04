#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include <bitset.h>

#define NUM_CELLS (20)

static void
_help( void ){

}

int 
main( int argc, char *argv[] ){
    
    int key;
    int result=0;
    bitcell_t set[NUM_CELLS];
    int index;
    bool m;

    if( 0 )
        _help();
    

    bitset_zeros( set, NUM_CELLS );
    index = bitset_peek( set, NUM_CELLS );
    
    bitset_ones( set, NUM_CELLS );
    index = bitset_peek( set, NUM_CELLS );

    key =131;

    bitset_zeros( set, NUM_CELLS );
    bitset_set( set, key );
    m = bitset_is_member(set,key);
    assert(m);
    index = bitset_peek( set, NUM_CELLS );
    assert(index!=-1);

    bitset_clear( set, key );
    m = bitset_is_member(set,key);
    assert(!m);
    index = bitset_peek( set, NUM_CELLS );
    assert(index==-1);

    return result;
}
