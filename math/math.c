#include <stdio.h>
#include "math.h"

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

unsigned long long 
factorial( int n ){

   return n==0 ? 1 : n * factorial(n-1) ;
}

long 
comb( int n, int k ){
   
   long value;
   
   if( n==0 )
      return -1;
   
   value = factorial(n) / (factorial(k) * factorial(n-k));
   return value;
}

long
perm( int n, int k ){
   long value;
   value = factorial(n) / factorial(n-k) ;
   return value;
}
