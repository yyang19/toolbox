#ifndef TOOLBOX_PSVV_HEADER
#define TOOLBOX_PSVV_HEADER

typedef struct{
   int n;
   int **comb;
   int ***cst;
}psvv_t;

psvv_t *psvv_init( int );
void psvv_destroy( psvv_t *);
int psvv_cst( psvv_t *, int, int, int );
#endif
