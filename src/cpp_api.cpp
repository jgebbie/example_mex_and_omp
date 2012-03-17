/*
 * Simple MEX interface
 */

#include "cpp_api.h"

#include <omp.h>
#include <stdio.h>

namespace std
{

double cpp_api ( double a, double b )
{
    int th_id, nthreads;
    #pragma omp parallel private(th_id)
    {
        th_id = omp_get_thread_num();
        printf ( "Hello World from thread %d\n", th_id );
        #pragma omp barrier
        if ( th_id == 0 ) {
            nthreads = omp_get_num_threads();
            printf ( "There are %d threads\n", nthreads );
        }
    }
    return a + b;
}

}
