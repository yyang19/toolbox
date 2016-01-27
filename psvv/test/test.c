#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include "psvv.h"

int
main(){

   int n;
   psvv_t *psvv;

   printf("Enter np : ");
   scanf("%d", &n );

   psvv = psvv_init( n );


   psvv_destroy(psvv);

   return 0;
}
