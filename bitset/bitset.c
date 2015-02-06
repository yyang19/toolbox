#include <stdio.h>
#include "bitset.h"

#define R2(n)     n,     n + 2*64,     n + 1*64,     n + 3*64
#define R4(n) R2(n), R2(n + 2*16), R2(n + 1*16), R2(n + 3*16)
#define R6(n) R4(n), R4(n + 2*4 ), R4(n + 1*4 ), R4(n + 3*4 )
static const unsigned char BitReverseTable256[256] = 
{
        R6(0), R6(2), R6(1), R6(3)
};

static const int
_deBruijn[32] = {
    0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8, 
    31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9
	};

INLINE void
bitset_zeros( bitset_t set, int n ) {
	int		i = 0;
	
	UNROLL( n, set[i] = 0; i ++; );
	}

INLINE void
bitset_ones( bitset_t set, int n ) {
	int		i = 0;
	
	UNROLL( n, set[i] = (bitcell_t)-1; i ++; );
	}

INLINE void
bitset_make_singleton( bitset_t set, int n, int i ) {
	bitcell_t*	cell 	= &set[i >> CLOG2_PER_CELL];
	int			index 	= i & MASK_PER_CELL;
	
	bitset_zeros( set, n );
	*cell = (0x1U << index);
	}
	
INLINE void
bitset_set( bitset_t set, int i ) {
	bitcell_t*	cell 	= &set[i >> CLOG2_PER_CELL];
	int			index 	= i & MASK_PER_CELL;
	
	*cell |= (0x1U << index);
	}

INLINE void
bitset_clear( bitset_t set, int i ) {
	bitcell_t*	cell 	= &set[i >> CLOG2_PER_CELL];
	int			index 	= i & MASK_PER_CELL;
	
	*cell &= ~(0x1U << index);
	}

	
INLINE bool
bitset_is_empty( bitset_t a, int n ) {
	int		i = 0;
	
	UNROLL( n, if( a[i] ) return false; i ++; );
	return true;
}

INLINE bool
bitset_is_full( bitset_t a, int n ) {
	int		i = 0;
	
	UNROLL( n, if( a[i] != (bitcell_t)-1 ) return false; i ++; );
	return true;
	}

INLINE bool
bitset_is_member( bitset_t set,  int i ) {
	bitcell_t*	cell 	= &set[i >> CLOG2_PER_CELL];
	int			index 	= i & MASK_PER_CELL;
	
	return (*cell & (0x1U << index)) ? true : false;
	}
	
INLINE void
bitset_union( bitset_t a, bitset_t b, int n ) {
	int		i = 0;
	
	UNROLL( n, a[i] |= b[i]; i ++; );
	}

INLINE void
bitset_intersect( bitset_t a, bitset_t b, int n ) {
	int		i = 0;
	
	UNROLL( n, a[i] &= b[i]; i ++; );
	}

INLINE void
bitset_diff( bitset_t a, bitset_t b, int n ) {
	int		i = 0;
	
	UNROLL( n, a[i] &= ~b[i]; i ++; );
	}

INLINE int
_bitset_first( bitset_t a, int n ) {
	int		i = 0;
	
	UNROLL( n, if( a[i] ) return i; i ++; );
	return -1;
	}

INLINE int
bitcell_peek( bitcell_t cell ) {
	return (_deBruijn[ (((cell & -cell) * 0x077CB531UL) & 0xffffffff) >> 27]);
	}

int
_bitcell_peek_mask( bitcell_t cell, int mask ) {

    bitcell_t c = cell & mask ;

	return (_deBruijn[ (((c & -c) * 0x077CB531UL) & 0xffffffff) >> 27]);
	}

int
_bitset_first_nonzero_mask( bitset_t a, int n, int *mask ) {
	int		i = 0;
	
	UNROLL( n, if( a[i] & mask[i] ) return i; i ++; );
	return -1;
	}

int
bitset_peek_mask( bitset_t set, int n, int *mask ) {
	
    int index;

    index = _bitset_first_nonzero_mask( set, n, mask );

	bitcell_t	cell;
	
	if( index >= 0 ) {
		cell = set[index];
		return (index << CLOG2_PER_CELL) | _bitcell_peek_mask( cell, mask[index] );
		}
	return -1;
	}


int 
bitset_reverse_word32( int v ){
    int c;

    c = (BitReverseTable256[v & 0xff] << 24) | 
        (BitReverseTable256[(v >> 8) & 0xff] << 16) | 
        (BitReverseTable256[(v >> 16) & 0xff] << 8) |
        (BitReverseTable256[(v >> 24) & 0xff]);

    return c;
}
INLINE bitcell_t
bitcell_pop( bitcell_t cell ) {
	cell &= cell - 1;
	return cell;
	}

INLINE int
bitcell_popcount( bitcell_t cell ) {
	bitcell_t		x = cell;
		
	x = x - ((x >> 1) & 0x55555555);
	x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
	x = (x + (x >> 4)) & 0x0F0F0F0F;
	x = x + (x >> 8);
	x = x + (x >> 16);
	return x & 0x0000003F;
 	}

INLINE int
bitset_peek( bitset_t set, int n ) {
	int			index = _bitset_first( set, n );
	bitcell_t	cell;
	
	if( index >= 0 ) {
		cell = set[index];
		return (index << CLOG2_PER_CELL) | bitcell_peek( cell );
		}
	return -1;
	}

INLINE void
bitset_pop( bitset_t set, int n ) {
	int			index = _bitset_first( set, n );
	
	if( index >= 0 ) 
		set[index] = bitcell_pop( set[index] );
	}

#define bitset_forall( set, n, i, j, cell )							\
	for( i = 0, cell = set[0]; i < n; i ++, cell = set[i] )			\
		for( j = bitcell_peek( cell ); cell != 0;					\
			 cell = bitcell_pop( cell ), j = bitcell_peek( cell ) )

INLINE int
bitset_count( bitset_t set, int n ) {
	int		count = 0;
	int		i;

	for( i = 0; i < n; i ++ )
		if( set[i] )
			count += bitcell_popcount( set[i] );
	return count;
	}

INLINE void
bitset_dump( bitset_t set, int n ) {
	int			i, j;
	bitcell_t	cell;
		
	bitset_forall( set, n, i, j, cell ) {
		printf( "%d ", (i << CLOG2_PER_CELL) + j );
		}
	}
	
	
