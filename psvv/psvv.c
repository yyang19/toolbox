#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<assert.h>
#include<math.h>
#include "psvv.h"


psvv_t *
psvv_init( int n ){

   int i,j;

   psvv_t *p;

   p = (psvv_t *) malloc (sizeof(psvv_t));

   if( !p )
      return p;

   p->n = n;

   p->comb = (int **) malloc ( sizeof(int *) * (p->n+1) ); 

   if( !p->comb )
      goto comb_p_fail;

   for( i=0; i<=p->n; i++ ){
      p->comb[i] = (int *) malloc ( sizeof(int) * (p->n+1) ); 
      if( !p->comb[i] )
         goto comb_i_fail;
   }

   for( i=0; i<=n; i++ ){
      for( j=0; j<=n; j++ )
         
         if( i==0 ){
            p->comb[i][j] = -1;
            continue;
         }
         else if( j<=i )
            p->comb[i][j] = comb( i, j );
         else
            p->comb[i][j] = -1;
   }

   goto done;

comb_i_fail:         
   for( j=i-1; j>=0; j-- )
      free( p->comb[j] );

comb_p_fail:
   free(p);
   p = NULL;

done:
   return p;
}

void
psvv_destroy( psvv_t *p ){

   int i;

   for( i=0; i<p->n; i++ )
      free( p->comb[i] );

   free(p);
}

int
psvv_cst( psvv_t *p, int t, int m, int n ){

   int sum;
   int j;

   if( t>n || m>n ){
      printf("Invalid input\n");
      return -1;
   }

   if( t == 0 )
      return 0;

   if( t == 1 && m == n-1 )
      return 1;

   if( t == 1 )
      return 0;

   assert( t>1 );

   if( m==0 && t==n )
      return 1;
   
   if( m<n-1 )
      return psvv_cst( p, t-1, m, n-1 );

   assert( m==n-1 );

   sum = 0;

   for( j=0; j<=n-2; j++ )
      sum += comb(n-1,j) * psvv_cst(p,t-1,j,n-1);

   return 1-sum;
}


