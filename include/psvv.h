#ifndef TOOLBOX_PSVV_HEADER
#define TOOLBOX_PSVV_HEADER

typedef struct{
   int n;
   int **comb;
}psvv_t;

psvv_t *psvv_init( int );
void psvv_destroy( psvv_t *);

#endif
