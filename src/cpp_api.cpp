/*
 * Simple MEX interface
 */

#include "cpp_api.h"

#include <omp.h>

namespace std
{

int cpp_api ( double* a, double* b, double* c )
{
    int th_id, nthreads;
    #pragma omp parallel private(th_id)
    {
        th_id = omp_get_thread_num();
        c[th_id] = a[th_id] + b[th_id];
        #pragma omp barrier
        if ( th_id == 0 )
            nthreads = omp_get_num_threads();
    }
    return nthreads;
}

}
