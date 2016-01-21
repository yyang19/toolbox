#include<stdlib.h>
#include<stdio.h>
#include<dice.h>
#include<stdbool.h>

void
dice_result_print( bool *arr, int count ){

   int i;

   for( i=0; i<count; i++ ){
      if( arr[i] )
         printf("hit\n");
      else
         printf("miss\n");
   }

   return;
}

int
main(){

   bool *arr;
   int len;
   float p;
   int seed;

   printf("Enter hit probability : ");
   scanf("%f", &p );
   printf("Enter sample size : ");
   scanf("%d", &len );
   printf("Enter seed number : ");
   scanf("%d", &seed );

   arr = (bool *) malloc ( sizeof(bool) * len );

   dice( 0.3, arr, len );
   dice_result_print(arr,len);
   
   printf("\n\n\n");

   dice_bernoulli( p, arr, len, seed );
   dice_result_print(arr,len);

   free(arr);

   return 0;
}
