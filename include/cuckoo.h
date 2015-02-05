#ifndef __HEADER_CUCKOO__
#define __HEADER_CUCKOO__

#define CK_HASH_INVALID_KEY ((int) ~0)

typedef struct{
    int key;
    void *value;
}cuckoo_kv_t;

typedef struct cuckoo{
    
    int sElem;
    int nElem;
    int nCell;
    int abort;
    int nOccupied;

    cuckoo_kv_t *buckets;
    cuckoo_kv_t *sorted_buckets;

    //hash functions
    int (* hash1)( struct cuckoo *, int);
    int (* hash2)( struct cuckoo *, int);

    //derived
    int nBucket;
    int size; //total hash table size in bytes

}cuckoo_t;

void cuckooReset( cuckoo_t *ct );
cuckoo_t * cuckooInit( int sElem, int nElem, int nCell, int abort );
void cuckooDestroy( cuckoo_t * ct );
bool cuckooPeek     ( cuckoo_t *, int, int, int, int );
bool cuckooInsert   ( cuckoo_t *table, cuckoo_kv_t elem, int attempt, int k, int c );
void * cuckooLookup( cuckoo_t *table, const int key );
void cuckooDelete( cuckoo_t *ct, const int key );

void cuckooFlush( cuckoo_t *ct );
void cuckooDump( cuckoo_t *ct );
#endif
