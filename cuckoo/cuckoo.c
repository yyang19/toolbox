/********************************************************
 * File:       cuckoo.c
 * AUthor:     Yue Yang (yueyang2010@gmail.com)
 * Description: key generic cuckoo hash table
 *******************************************************/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "cuckoo.h"

static int
hash1( cuckoo_t *ct, int key ){

    key = ~key + (key << 15); // key = (key << 15) - key - 1;
    key = key ^ (key >> 12);
    key = key + (key << 2);
    key = key ^ (key >> 4);
    key = key * 2057; // key = (key + (key << 3)) + (key << 11);
    key = key ^ (key >> 16);
    
    return key % ct->nBucket;
}

static int
hash2( cuckoo_t *ct, int key ){
    
    key = (key+0x7ed55d16) + (key<<12);
    key = (key^0xc761c23c) ^ (key>>19);
    key = (key+0x165667b1) + (key<<5);
    key = (key+0xd3a2646c) ^ (key<<9);
    key = (key+0xfd7046c5) + (key<<3);
    key = (key^0xb55a4f09) ^ (key>>16);
    
    return key % ct->nBucket;
}


void 
cuckooReset( cuckoo_t *ct )
{
    memset(ct->buckets, 0xff, ct->size );
    memset(ct->sorted_buckets, 0xff, ct->size );
    ct->nOccupied = 0;
}


cuckoo_t *
cuckooInit( int sElem, 
            int nElem, 
            int nCell, 
            int abort )
{
    cuckoo_t *ct;

    ct = (cuckoo_t *)malloc( sizeof(cuckoo_t) );

    if( !ct )
        return NULL;

    ct->sElem = sElem;
    ct->nElem = nElem;
    ct->nCell = nCell;
    ct->abort = abort;
    ct->nOccupied = 0;

    ct->hash1 = hash1;
    ct->hash2 = hash2;
    
    ct->size = sElem*nElem;
    ct->nBucket = nElem / nCell;
    if( nElem % nCell > 0 )
        ++ct->nBucket;

    ct->buckets = malloc( ct->size * sizeof(cuckoo_kv_t) );

    if( !ct->buckets ){
        free( ct );
        return NULL;
    }
    
    ct->sorted_buckets = malloc( ct->size * sizeof(cuckoo_kv_t) );

    if( !ct->sorted_buckets ){
        free( ct->buckets );
        free( ct );
        return NULL;
    }
    
    memset(ct->buckets, 0xff, ct->size);
    memset(ct->sorted_buckets, 0xff, ct->size);

    return ct;
}

void
cuckooDestroy( cuckoo_t * ct )
{
    free( ct->sorted_buckets );
    free( ct->buckets );
    free( ct );
}

bool
cuckooPeek( cuckoo_t *ct, 
            int key, 
            int attempt, 
            int k, int c )
{
    int k1, k2, ki, ci;
    int kickout;

    bool success = false;

    if( attempt < ct->abort ){
        k1 = ct->hash1(ct,key);
        for(ci=0; ci<ct->nCell; ++ci){
            if(ct->buckets[ k1*ct->nCell+ci ].key == CK_HASH_INVALID_KEY){
        		success = true;
                goto out;   
            }
        }

        k2 = ct->hash2(ct,key);
        for(ci=0; ci<ct->nCell; ++ci){
            if(ct->buckets[ k2*ct->nCell+ci ].key == CK_HASH_INVALID_KEY){
		        success = true;
                goto out;
            }
        }

        if( k==k1 )
            ki=k2;
        else
            ki=k1;        

        if( ci==c )
            ci = attempt+1;

        ci = ci % ct->nCell;

        kickout = ct->buckets[ki*ct->nCell+ci].key;

    	success = cuckooPeek( ct, kickout, ++attempt, ki, ci ) ;
    }

out:
    return success;
}

bool
cuckooInsert( cuckoo_t *ct, cuckoo_kv_t elem, int attempt, int k, int c )
{
    int k1, k2, ki, ci;
    cuckoo_kv_t kickout;
    cuckoo_kv_t e;
    bool success=false;

    e.key   = elem.key; 
    e.value = elem.value;

    if( attempt < ct->abort ){
        k1 = ct->hash1(ct,elem.key);
        for(ci=0; ci<ct->nCell; ++ci){
            if(ct->buckets[k1*ct->nCell+ci].key == CK_HASH_INVALID_KEY){
                ct->buckets[k1*ct->nCell+ci] = e;
                ++ ct->nOccupied;   
                success = true;
        		goto out;   
            }
        }

        k2 = ct->hash2(ct,elem.key);
        for(ci=0; ci<ct->nCell; ++ci){
            if(ct->buckets[k2*ct->nCell+ci].key == CK_HASH_INVALID_KEY){
                ct->buckets[k2*ct->nCell+ci] = e;
                ++ ct->nOccupied;   
                success = true;
        		goto out;
            }
        }

        if( k==k1 )
            ki=k2;
        else
            ki=k1;        

        if( ci==c )
            ci = attempt+1;
        ci = ci % ct->nCell;

        kickout = ct->buckets[ki*ct->nCell+ci];
        ct->buckets[ki*ct->nCell+ci] = e;

    	success = cuckooInsert( ct, kickout, ++attempt, ki, ci ) ;
    }

out:
    assert( success );
    return success;
}

void *
cuckooLookup( cuckoo_t *ct, const int key )
{
    int k, ki;
    void *value = NULL;;

    if(key != CK_HASH_INVALID_KEY)
        return value;

    k = ct->hash1(ct,key);
    assert( k < ct->nBucket );
    
    for(ki=0; ki<ct->nCell; ++ki)
        if(ct->buckets[k*ct->nCell+ki].key == key)            
            return ct->buckets[k*ct->nCell+ki].value;

    k = ct->hash2(ct,key);
    assert( k < ct->nBucket );

    for(ki=0; ki<ct->nCell; ++ki)
        if(ct->buckets[k*ct->nCell+ki].key == key)            
            return ct->buckets[k*ct->nCell+ki].value;

    return value;
}

void
cuckooDelete( cuckoo_t *ct, int key )
{
    int k, ki;

    if( key == CK_HASH_INVALID_KEY )
        return;

    k = ct->hash1(ct,key);
    assert( k < ct->nBucket );
    
    for(ki=0; ki<ct->nCell; ++ki)
        if(ct->buckets[k*ct->nCell+ki].key == key){
            ct->buckets[k*ct->nCell+ki].key = CK_HASH_INVALID_KEY;
            ct->buckets[k*ct->nCell+ki].value = NULL;
            return;
        }

    k = ct->hash2(ct,key);
    assert( k < ct->nBucket );
    
    for(ki=0; ki<ct->nCell; ++ki)
        if(ct->buckets[k*ct->nCell+ki].key == key){
            ct->buckets[k*ct->nCell+ki].key = CK_HASH_INVALID_KEY;
            ct->buckets[k*ct->nCell+ki].value = NULL;
            return;
        }

    return;
}

void
cuckooFlush( cuckoo_t* ct ){
    //flush elements in the table
    
    cuckooReset( ct );

    return;
}

void
cuckooDump( cuckoo_t *ct )
{
    int i;

    printf("Cuckoo hash table dump\n");

    for(i=0; i<ct->nElem; ++i){
        if(ct->buckets[i].key != CK_HASH_INVALID_KEY){
            printf("elem #%d: key <%d>\n", i, ct->buckets[i].key);       
        }
    }

    return;
}


/*
void
cuckooUpdate(cuckoo_t *ct, int index, cuckoo_kv_t elem )
{
    uint32_t k, bucket, ki;
    ck_val_t oldVal;

    if( elem.key != CK_HASH_INVALID_KEY )
        return;

    assert( ct->buckets[index].key == key );

    ct->buckets[index].old = table->buckets[index].val ;
    ct->buckets[index].val = val; 
}
*/
