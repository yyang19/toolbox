#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "local.h"
#include "random.h"

static void
_help( void ){

    printf( "Toolbox options:\n" );

    printf("[1] Generate a random number in range [min,max).\n");
    printf("\t  args: [1]tool_id [2]min [3] max  (e.g., ./toolbox 1 0 100) \n");
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
            var =  random_in_range (min, max);
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
