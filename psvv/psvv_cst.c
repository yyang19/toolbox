#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<math.h>
#include<assert.h>
#include "psvv_cst.h"

#define INVALID_CST ( (long double)~0 )

psvv_t *
psvv_cst_init( int n ){

   int i,j,k;

   psvv_t *p;

   p = (psvv_t *) malloc (sizeof(psvv_t));

   if( !p )
      return p;

   p->n = n;

   p->comb = (long double **) malloc ( sizeof(long double *) * (p->n+1) ); 

   if( !p->comb )
      goto comb_p_fail;

   for( i=0; i<=p->n; i++ ){
      p->comb[i] = (long double *) malloc ( sizeof(long double) * (p->n+1) ); 
      if( !p->comb[i] )
         goto comb_i_fail;
   }

   p->cst = (long double ***) malloc (sizeof(long double **) * (p->n+1) );

   if( !p->cst )
       goto cst_fail;

   for( i=0; i<=n; i++ ){
      p->cst[i] = (long double **) malloc ( sizeof(long double*) * (p->n+1) ); 
      if( !p->cst[i] )
         goto cst_i_fail;
      for( j=0; j<=n; j++ ){
          p->cst[i][j] = (long double *) malloc ( sizeof(long double) * (p->n+1) ); 
          if( !p->cst[i][j] )
              goto cst_j_fail;
      }
   }

   for( i=0; i<=n; i++ ){
      for( j=0; j<=n; j++ )
         
         if( i==0 ){
            if( j==0 )
                p->comb[i][j] = 1;
            else
                p->comb[i][j] = -1;
            continue;
         }
         else if( j<=i )
            p->comb[i][j] = comb( i, j );
         else
            p->comb[i][j] = -1;
   }
   
   for( i=0; i<=n; i++ ){
      for( j=0; j<=n; j++ )
          for( k=0; k<=n; k++ )
              p->cst[i][j][k] = INVALID_CST;
   }

   goto done;

cst_j_fail:
   for( k=j-1; k>=0; k-- )
       free( p->cst[i][k] );

cst_i_fail:
   for( j=i-1; j>=0; j-- ){
       for( k=0; k<=p->n; k++ ){
           free( p->cst[j][k] );
           }
       free( p->cst[j] );
   }
cst_fail:
   i=p->n+1;

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
psvv_cst_destroy( psvv_t *p ){

   int i;

   for( i=0; i<p->n; i++ )
      free( p->comb[i] );

   free(p);
}

long double
psvv_cst_get0( psvv_t *p, int t, int m, int n ){

   long double sum;
   int j;
   long double value;
   long double tmp;

   if( t>n || m>n ){
      printf("Invalid input\n");
      return -1;
   }
   
   if( p->cst[t][m][n] != INVALID_CST )
       return p->cst[t][m][n];

   if( t == 0 ){
      value = 0;
      goto done;
   }

   if( t == 1 && m == n-1 ){
      value = 1;
      goto done;
   }

   if( t == 1 ){
      value = 0;
      goto done;
   }

   assert( t>1 );

   if( m==0 && t==n ){
      value = 1;
      goto done;
   }
   
   if( m<n-1 ){
      value = psvv_cst_get0( p, t-1, m, n-1 );
      goto done;
   }

   assert( m==n-1 );

   sum = 0;

   for( j=0; j<=n-2; j++ ){
      tmp = ((long double) p->comb[n-1][j]) * psvv_cst_get0(p,t-1,j,n-1);
      sum += tmp;
   }

   value = 1-sum;

done:
   p->cst[t][m][n] = value;
   return value;
}

void
cst_dump( psvv_t *p, int n, int t )
{
   int j;

   int tmp;
   long tmp_l;
   long double tmp_ld;
   long double sum = 0;
   
   for( j=0; j<=n-2; j++ ){
      tmp = p->comb[n-1][j] * p->cst[t-1][j][n-1];
      tmp_l = ((long) p->comb[n-1][j]) * p->cst[t-1][j][n-1];
      tmp_ld = ((long double) p->comb[n-1][j]) * p->cst[t-1][j][n-1];
      sum += tmp_ld;
      printf( "%d, %ld, %Lf\n", tmp, tmp_l, tmp_ld);
   }
}

long
psvv_cst_get( psvv_t *p, int t, int m, int n ){

    long value;

    if( t==n && m==0 )
        value = 1;
    else if( n-m<=t && t<=n ){
        value = ( (t+m+n)%2 == 0 ) ? 1 : -1;
        value *= p->comb[m-1][t+m-n];
    }
    else 
        value = 0;

    return value;
}

