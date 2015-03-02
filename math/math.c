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

