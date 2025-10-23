#include "jacobi.h"
#include <math.h>
#include <cmath>
#include <omp.h>

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
    const double denom = double(p.nx) * double(p.ny);
    double sum = 0.0;

    #pragma omp parallel for collapse(2) reduction(+:sum) schedule(static)
    for (int i = 0; i < p.nx; ++i){
        for (int j = 0; j < p.ny; ++j){
            const double d = mat1[i][j] - mat2[i][j];
            sum += d * d;
        }
    }
    return std::sqrt(sum / denom);
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
void jacobi_step(params p, double** u_new, double** u_old, double** f){
    const double dx   = 1.0 / double(p.nx - 1);
    const double dy   = 1.0 / double(p.ny - 1);
    const double idx2 = 1.0 / (dx * dx);
    const double idy2 = 1.0 / (dy * dy);
    const double denom = 2.0 * (idx2 + idy2);

    #pragma omp parallel
    {
        
        #pragma omp for collapse(2) schedule(static)
        for (int i = 0; i < p.nx; ++i)
            for (int j = 0; j < p.ny; ++j)
                u_old[i][j] = u_new[i][j];

        
        #pragma omp for schedule(static)
        for (int j = 0; j < p.ny; ++j){
            u_new[0][j]        = f[0][j];
            u_new[p.nx-1][j]   = f[p.nx-1][j];
        }
        #pragma omp for schedule(static)
        for (int i = 0; i < p.nx; ++i){
            u_new[i][0]        = f[i][0];
            u_new[i][p.ny-1]   = f[i][p.ny-1];
        }

        
        #pragma omp for collapse(2) schedule(static)
        for (int i = 1; i < p.nx - 1; ++i){
            for (int j = 1; j < p.ny - 1; ++j){
                u_new[i][j] = ( idx2*(u_old[i-1][j] + u_old[i+1][j])
                              + idy2*(u_old[i][j-1] + u_old[i][j+1])
                              - f[i][j] ) / denom;
            }
        }
    } 
}
