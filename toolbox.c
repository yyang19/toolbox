#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "local.h"

static void
_help( void ){

    printf( "Toolbox options:\n" );

    printf("[1] Generate a random number in range [min,max).\n");
    printf("\t  args: [1]tool_id [2]min [3] max  (e.g., ./toolbox 1 0 100) \n");
}

/* * _random_in_range
 * Description: generate a random number in [min,max)
 * @min : lower bound
 * @max : upper bound
 * return : a random number in [min,max)
 */
static int 
_random_in_range (unsigned int min, unsigned int max){
    
    int base_random = rand(); /* in [0, RAND_MAX] */
    
    if (RAND_MAX == base_random) return _random_in_range(min, max);
    
    int range       = max - min,
    remainder   = RAND_MAX % range,
    bucket      = RAND_MAX / range;
    
    if (base_random < RAND_MAX - remainder) 
       return min + base_random/bucket;
    else 
       return _random_in_range (min, max);
}

int 
main( int argc, char *argv[] ){

    int result;
    int tool_id;
    int var;
    int min,max;

    if( argc<2 )
        goto help;

    tool_id = atoi(argv[1]);

    result = 0 ;

    switch (tool_id){
    
        case 1:
            if( argc != 4 )
                goto help;

            min = atoi(argv[2]);
            max = atoi(argv[3]);
            var =  _random_in_range (min, max);
            printf("Result variable: %d\n", var);
            break;
        default:
            printf("Not a valid tool ID\n");
            break;                    
    }

    if( result == 0 )
        goto out;
help:    
    _help();
    result = -1;

out:    
    return result;
}
