#ifndef _HEADER_BITSET_
#define _HEADER_BITSET_

#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>

#ifndef INLINE
#ifdef DEBUG
#define INLINE
#else
#define INLINE inline
#endif
#endif

/*********************************************************************
 * Unroll pattern
 *********************************************************************/
#ifndef UNROLL
#define UNROLL(len, st) {						\
		int _n = len;							\
		assert( _n >= 0 );						\
		while( _n -- ) {						\
				st	}							\
		}
#endif

#define BITS_PER_CELL		(32)
#define CLOG2_PER_CELL		(5)
#define MASK_PER_CELL		(BITS_PER_CELL-1)

typedef uint32_t		bitcell_t;
typedef bitcell_t		bitset_t[];

void bitset_zeros( bitset_t set, int n );
void bitset_ones( bitset_t set, int n );
bool bitset_is_empty( bitset_t a, int n );
bool bitset_is_full( bitset_t set, int n );
int bitset_peek( bitset_t set, int n );

void bitset_set( bitset_t set, int i );
void bitset_clear( bitset_t set, int i );
bool bitset_is_member( bitset_t set,  int i );

int bitset_peek_mask( bitset_t set, int n, int *mask );
#endif
