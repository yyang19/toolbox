#include<stdlib.h>
#include<gsl/gsl_math.h>
#include<gsl/gsl_randist.h>
#include<stdbool.h>

long rand_vald(int seed);
double unifd(int min, int max);

void
dice( double p, bool *arr, int count ){
   
   const gsl_rng_type * T;
   gsl_rng * r;
   int i;

   if( p<0 || p>1 ){
      printf("Invalid p value\n");
      return;
   }
   
   gsl_rng_env_setup();

   T = gsl_rng_default;
   r = gsl_rng_alloc (T); 
   
   for( i=0; i<count; i++ )
      arr[i] = gsl_ran_bernoulli(r,p);

   gsl_rng_free(r);
}

void
dice_bernoulli( double p, bool *arr, int count, int seed ){
   
   int i;
   double var;
   
   if( p<0 || p>1 ){
      printf("Invalid p value\n");
      return;
   }

   rand_vald(seed);
   
   for( i=0; i<count; i++ ){
      var = unifd( 0, 1 );
      if( var <= p )
         arr[i] = 1;
      else
         arr[i] = 0;
   }

   return;
}

double 
unifd(int min, int max)
{
  int    z;                     // Uniform random integer number
  int    unif_value;            // Computed uniform value to be returned

  // Pull a uniform random integer
  z = rand_vald(0);

  // Compute uniform discrete random variable using inversion method
  unif_value = z % (max - min + 1) + min;

  return(unif_value);
}

//=========================================================================
//= Multiplicative LCG for generating uniform(0.0, 1.0) random numbers    =
//=   - From R. Jain, "The Art of Computer Systems Performance Analysis," =
//=     John Wiley & Sons, 1991. (Page 443, Figure 26.2)                  =
//=========================================================================
long rand_vald(int seed)
{
  const long  a =      16807;  // Multiplier
  const long  m = 2147483647;  // Modulus
  const long  q =     127773;  // m div a
  const long  r =       2836;  // m mod a
  static long x;               // Random int value
  long        x_div_q;         // x divided by q
  long        x_mod_q;         // x modulo q
  long        x_new;           // New x value

  // Set the seed if argument is non-zero and then return zero
  if (seed > 0)
  {
    x = seed;
    return(0.0);
  }

  // RNG using integer arithmetic
  x_div_q = x / q;
  x_mod_q = x % q;
  x_new = (a * x_mod_q) - (r * x_div_q);
  if (x_new > 0)
    x = x_new;
  else
    x = x_new + m;

  // Return a random integer number
  return(x);
}
