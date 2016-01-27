#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include "psvv.h"

int
main(){

   int n, m, t, c, np;
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
              c = psvv_cst( psvv, t, m , n ); 
              printf("t=%d, m=%d, n=%d, c=%d\n", t, m, n, c);
           }

   psvv_destroy(psvv);

   return 0;
}
