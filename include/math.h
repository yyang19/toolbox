#ifndef _HEADER_MATH_
#define _HEADER_MATH_

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

int PowerOfTwo(unsigned val);
int roundUpPowerOf2(int);
int factorial( int );
long comb( int, int );
long perm( int, int );

#endif
