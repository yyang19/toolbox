#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>




static void 
_quicksort_recur( int *x, int first, int last )
{
    int pivot,j, i;
    int temp;

    if(first<last){
        pivot=first;
        i=first;
        j=last;
        
        while(i<j){
            while( x[i] <= x[pivot] && i<last )
                i++;
            while( x[j] >x[pivot] )
                j--;
            if(i<j){
                temp=x[i];
                x[i]=x[j];
                x[j]=temp;
            }
        }
        
        temp=x[pivot];
        x[pivot]=x[j];
        x[j]=temp;

        _quicksort_recur(x,first,j-1);
        _quicksort_recur(x,j+1,last);
    }
}

// A utility function to swap two elements
void swap ( int* a, int* b )
{
    int t = *a;
    *a = *b;
    *b = t;
}

/* This function is same in both iterative and recursive*/
int partition (int arr[], int l, int h)
{
    int x = arr[h];
    int i = (l - 1);
    int j;
    
    for(j = l; j <= h- 1; j++)
    {
        if (arr[j] <= x)
        {
            i++;
            swap (&arr[i], &arr[j]);
        }
    }
    swap (&arr[i + 1], &arr[h]);
    return (i + 1);
}


static void
_quicksort_non_recur0( int *arr, int first, int last )
{
    //Create an auxiliary stack
    int stack[last-first+1];
         
    //initialize top of stack
     int top = -1;
      
     // push initial values of first and last to stack
    stack[ ++top ] = first;
    stack[ ++top ] = last;
    
    // Keep popping from stack while is not empty
    while ( top >= 0 )
    {
        // Pop last and first
        last = stack[ top-- ];
        first = stack[ top-- ];
        
        // Set pivot element at its correct position in sorted array
        int p = partition( arr, first, last );
        // If there are elements on left side of pivot, then push left
        // side to stack
        if ( p-1 > first )
        {
            stack[ ++top ] = first;
            stack[ ++top ] = p - 1;
        }
        
        // If there are elements on right side of pivot, then push right
        // side to stack

        if ( p+1 < last )
        {
            stack[ ++top ] = p + 1;
            stack[ ++top ] = last;
            
        }
    }
}

static void
_quicksort_non_recur1( int *arr, int first, int last )
    
    #define MAX_LEVELS (1000)

    int  piv, beg[MAX_LEVELS], end[MAX_LEVELS], i=0, L, R ;

    beg[0]=0; 
    end[0]=last+1;

    while (i>=0) {
        L=beg[i]; R=end[i]-1;
        if (L<R) {
            piv=arr[L]; 
            if (i==MAX_LEVELS-1) 
                assert(0);
            
            while (L<R) {
                  while (arr[R]>=piv && L<R) R--; if (L<R) arr[L++]=arr[R];
                  while (arr[L]<=piv && L<R) L++; if (L<R) arr[R--]=arr[L];
            }

            arr[L]=piv; 
            beg[i+1]=L+1; 
            end[i+1]=end[i]; 
            end[i++]=L; 
        }
        else 
           i--; 
    }
}

void
quicksort( int *array, int start, int end, bool recursive )
{
    if( recursive )
        _quicksort_recur( array, start, end );
    else
        _quicksort_non_recur1( array, start, end );
}
