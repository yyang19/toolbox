#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include <cuckoo.h>


static void
_help( void ){

}

int 
main( int argc, char *argv[] ){

    cuckoo_t *ck_table;
    int sElem, nElem, nCell, abort;
    int result=0;
    bool avail;
    int key;
    cuckoo_kv_t kv;

    if( 0 )
        _help();

    sElem = sizeof(cuckoo_kv_t);
    nElem = 8192;
    nCell = 4;
    abort = 10;
    
    ck_table = cuckooInit(sElem, nElem, nCell, abort );

    assert( ck_table );

    for( key=0; key<128; key++ ){
        avail = cuckooPeek( ck_table, key, 0, -1, -1 );

        if( avail ){
            kv.key = key;
            kv.value = &key;
            result = cuckooInsert( ck_table, kv, 0, -1, -1 ); 
        }
        else
            cuckooFlush( ck_table );
    }
    
    cuckooDump( ck_table );
    
    for( key=0; key<128; key++ )
        cuckooDelete( ck_table, key );
    
    cuckooDump( ck_table );

    cuckooDestroy( ck_table );

    return result;
}
