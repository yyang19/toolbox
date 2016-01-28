#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include "psvv.h"

int
main(){

   int n, m, t, c1, c2, np;
   psvv_t *psvv;

   printf("Enter np : ");
   scanf("%d", &np );

   psvv = psvv_init( np );

   if( !psvv ){
       printf("Init failed\n");
       return -1;
   }

   for( n=1; n<=np; n++ )
       for( m=1; m<n; m++ )
           for( t=0; t<n; t++ ){
              c1 = psvv_cst( psvv, t, m , n ); 
              c2 = psvv_cst2( psvv, t, m , n ); 
              printf("t=%d, m=%d, n=%d, c1=%d, c2=%d\n", t, m, n, c1, c2);
              if( c1 != c2 ){
                  printf("Discrepency found!\n");
                  //return -1;
              }
           }

   psvv_destroy(psvv);

   return 0;
}
