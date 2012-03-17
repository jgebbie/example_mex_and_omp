/*
 * Simple MEX interface
 */

#include "cpp_api.h"

#include <omp.h>

namespace std
{

int cpp_api ( double* a, double* b, double* c, int len )
{
    int th_id, nthreads;
    #pragma omp parallel private(th_id)
    {
        nthreads = omp_get_num_threads();
        th_id = omp_get_thread_num();
        int i = th_id * len / nthreads;
        int j = ( th_id + 1 ) * len / nthreads;
        for ( ; i < j; ++i )
            c[i] = a[i] + b[i];
        #pragma omp barrier
    }
    return nthreads;
}

}
