#ifndef TOOLBOX_PSVV_HEADER
#define TOOLBOX_PSVV_HEADER

typedef struct{
   int n;
   long double **comb;
   long double ***cst;
}psvv_t;

psvv_t *psvv_cst_init( int );
void psvv_cst_destroy( psvv_t *);
long double psvv_cst_get0( psvv_t *, int, int, int );
long psvv_cst_get( psvv_t *, int, int, int );
#endif
