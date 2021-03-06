/*
 * Simple MEX interface
 */

using namespace std;

#include "mex.h"

#include "cpp_api.h"

#define TOOLBOX "AOR"

void mexFunction ( int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[] )
{
    /* check for proper number of arguments */
    if ( nrhs != 2 ) {
        mexErrMsgIdAndTxt ( TOOLBOX ":mex_api:nrhs",
                            "Two inputs required." );
        return;
    }
    if ( nlhs != 1 ) {
        mexErrMsgIdAndTxt ( TOOLBOX ":mex_api:nlhs",
                            "One output required." );
        return;
    }

    /* make sure the first input argument is of the correct data type */
    if ( !mxIsDouble ( prhs[0] ) ) {
        mexErrMsgIdAndTxt ( TOOLBOX ":mex_api:notScalar",
                            "First input must be a double." );
        return;
    }

    /* make sure the second input argument is of the correct data type */
    if ( !mxIsDouble ( prhs[1] ) ) {
        mexErrMsgIdAndTxt ( TOOLBOX ":mex_api:notScalar",
                            "Second input must be a double." );
        return;
    }

    /* make sure the size of the first and second input arguments match */
    if ( mxGetNumberOfElements ( prhs[0] ) != mxGetNumberOfElements ( prhs[1] ) ) {
        mexErrMsgIdAndTxt ( TOOLBOX ":mex_api:notScalar",
                            "Number of elements in each input argument must match." );
        return;
    }

    /* make sure the size of the first and second input arguments match */
    if ( mxGetNumberOfElements ( prhs[0] ) < 2 ) {
        mexErrMsgIdAndTxt ( TOOLBOX ":mex_api:notSize",
                            "Each input vector must have at least two elements." );
        return;
    }

    /* number of elements to multiply together */
    int n = mxGetNumberOfElements ( prhs[0] );

    /* create the output matrix */
    plhs[0] = mxCreateDoubleMatrix ( 1, n, mxREAL );

    double* a = mxGetPr ( prhs[0] );
    double* b = mxGetPr ( prhs[1] );
    double* c = mxGetPr ( plhs[0] );

    int nthreads = cpp_api ( a, b, c, n );

    //printf ( "nthreads=%d\n", nthreads );
}
