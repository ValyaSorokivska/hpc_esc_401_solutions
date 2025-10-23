#include <omp.h>

void jacobi_step(params p, double** u_new, double** u_old, double** f){
    const double dx   = 1.0 / double(p.nx - 1);
    const double dy   = 1.0 / double(p.ny - 1);
    const double idx2 = 1.0 / (dx * dx);
    const double idy2 = 1.0 / (dy * dy);
    const double denom = 2.0 * (idx2 + idy2);

    #pragma omp parallel
    {
        // 1) Save previous iterate: u_old <- u_new
        #pragma omp for collapse(2) schedule(static)
        for (int i = 0; i < p.nx; ++i)
            for (int j = 0; j < p.ny; ++j)
                u_old[i][j] = u_new[i][j];

        // 2) Dirichlet boundaries from f (four edges)
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

        // 3) Interior Jacobi update
        #pragma omp for collapse(2) schedule(static)
        for (int i = 1; i < p.nx - 1; ++i){
            for (int j = 1; j < p.ny - 1; ++j){
                u_new[i][j] = ( idx2*(u_old[i-1][j] + u_old[i+1][j])
                              + idy2*(u_old[i][j-1] + u_old[i][j+1])
                              - f[i][j] ) / denom;
            }
        }
    } // parallel
}
