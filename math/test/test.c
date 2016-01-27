#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <assert.h>

#include <math.h>

static void
_help( void ){

    return;
}

int 
main( int argc, char *argv[] ){

    int result = 0;

    int value;
    int var;

    if( 0 )
        _help();

    for( var=0; var<100; var++ ){
        value = roundUpPowerOf2(var);
        printf("var = %d, next power of 2: %d\n" ,var,value);
    }

    result = comb( 10 ,2 );

    printf("result %d\n", result);

    return result;
}
