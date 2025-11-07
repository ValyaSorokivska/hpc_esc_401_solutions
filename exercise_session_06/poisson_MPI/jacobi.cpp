#include "jacobi.h"
#include <math.h>
#include "mpi_module.h"

/**
 * @brief      Computes norm of the difference between two matrices
 *
 * @param[in]  p     Parameters
 * @param      mat1  The matrix 1
 * @param      mat2  The matrix 2
 *
 * @return     Returns \sqrt{\sum(mat1_{ij} - mat2_{ij})^2/(nx*ny)}
 */
double norm_diff(params p, double** mat1, double** mat2){

    double loc = 0.0;
    for (int i = p.xmin; i < p.xmax; ++i) {
        for (int j = p.ymin; j < p.ymax; ++j) {
            const int ix = i - p.xmin;
            const int iy = j - p.ymin;
            const double d = mat1[ix][iy] - mat2[ix][iy];
            loc += d * d;
        }
    }

    // global reduction
    double glob = 0.0;
    ALLREDUCE(&loc, &glob);   

    // over entire grid
    return sqrt( glob / ( (double)p.nx * (double)p.ny ) );
}

/**
 * @brief      Compute a Jacobi iteration to solve Poisson equation. This function updates
 *             u_new and u_old in-place.
 *
 * @param[in]  p      Parameters
 * @param      u_new  The new solution
 * @param      u_old  The old solution
 * @param      f      The source term
 */
void jacobi_step(params p, double** u_new, double** u_old, double** f, int my_rank, int size){
    double dx = 1.0/((double)p.nx - 1);
    double dy = 1.0/((double)p.ny - 1);

    double* fromLeft = new double[p.ymax - p.ymin]; 
    double* fromRight = new double[p.ymax - p.ymin];

    for (int i = p.xmin; i < p.xmax; ++i)
        for (int j = p.ymin; j < p.ymax; ++j)
            u_old[i - p.xmin][j - p.ymin] = u_new[i - p.xmin][j - p.ymin];

    
    halo_comm(p, my_rank, size, u_old, fromLeft, fromRight);

    for (int i = p.xmin; i < p.xmax; ++i) {
        if (i == 0 || i == p.nx - 1) continue;
        for (int j = p.ymin; j < p.ymax; ++j) {
            if (j == 0 || j == p.ny - 1) continue;

            const int ix = i - p.xmin;
            const int iy = j - p.ymin;

            //handle slab edges 
            double leftN, rightN;
            if (ix == 0)            leftN  = fromLeft[iy];
            else                    leftN  = u_old[ix - 1][iy];

            if (ix == nx_loc - 1)   rightN = fromRight[iy];
            else                    rightN = u_old[ix + 1][iy];

            // neighbors in y are inside the same slab
            double downN = u_old[ix][iy - 1];
            double upN   = u_old[ix][iy + 1];

            //new formula
            u_new[ix][iy] = 0.25 * ( leftN + rightN + downN + upN
                                     - dx * dy * f[ix][iy] );
        }
    }
    if (p.nx!=p.ny) printf("In function jacobi_step (jacobi.cpp l.26): nx != ny, check jacobi updates\n");
}
