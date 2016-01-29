#include <stdio.h>
#include "math.h"

#define PI (3.1415926)

int PowerOfTwo(unsigned val)
{
    return val && (!(val & (val - 1)));
}

int
roundUpPowerOf2(int v){

    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    
    return v;
}

long double
factorial( int n ){

   return n==0 ? 1 : n * factorial(n-1) ;
}

long double
comb( int n, int k ){
   int i; 
   long double value;
   long double prod; 
   if( n==0 )
      return -1;

#if 0
   // note that built-in data type supports upto to 28!
   value = factorial(n) / (factorial(k) * factorial(n-k));
#else   
   if( k>n/2 )
      return comb(n,n-k);

   prod = 1;
   for( i=n; i>n-k; i-- )
      prod *= (long double)i;

   value = prod / factorial(k);
#endif
   return value;
}

long
perm( int n, int k ){
   long value;
   value = factorial(n) / factorial(n-k) ;
   return value;
}
