#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
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
    int i;
    int mask[NUM_CELLS];
    int cellmask = 0xffff;
    int last_peek;

    if( 0 )
        _help();
    
    bitset_zeros( set, NUM_CELLS );
    index = bitset_peek( set, NUM_CELLS );
    assert( index==-1 );
    
    bitset_ones( set, NUM_CELLS );
    index = bitset_peek( set, NUM_CELLS );
    assert( index==0 );

    bitset_zeros( set, NUM_CELLS );
    for( key=NUM_CELLS*CHAR_BIT*sizeof(int)-1;key>=0; key-- ){
        bitset_set( set, key );
        m = bitset_is_member(set,key);
        assert(m);
        index = bitset_peek( set, NUM_CELLS );
        assert(index==key);
    }

    for( key=0; key<NUM_CELLS*CHAR_BIT*sizeof(int)-1; key++ ){
        bitset_clear( set, key );
        m = bitset_is_member(set,key);
        assert(!m);
        index = bitset_peek( set, NUM_CELLS );
        assert(index==key+1);
    }
    
    // Mask tests
    bitset_zeros( set, NUM_CELLS );
    
    for( i=0; i<NUM_CELLS; i++ )
        mask[i] = cellmask;
    
    last_peek = -1;

    for( key=NUM_CELLS*CHAR_BIT*sizeof(int)-1;key>=0; key-- ){
        bitset_set( set, key );
        index = bitset_peek_mask( set, NUM_CELLS, mask );
        assert( index == ( (key & 31 )> 0xf ? last_peek : key));
        if( index != -1 )
            last_peek = index;
    }

    return result;
}
