#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <mpi.h>
#include "gettime.h"

static long   nSteps = 100000000;                // 1e8 steps; adjust if needed
static double PI25DT = 3.141592653589793238462643;

int main(int argc, char **argv)
{
    double prog0 = getTime();                    // total program start

    MPI_Init(&argc, &argv);
    double mpi0  = getTime();                    // MPI-only start

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double h   = 1.0 / (double)nSteps;
    double sum = 0.0, x;

    // block-cyclic over i
    for (long i = rank; i < nSteps; i += size) {
        x = h * ((double)i - 0.5);
        sum += 4.0 / (1.0 + x * x);
    }

    double global_sum = 0.0;
    MPI_Reduce(&sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    double mpi1  = getTime();                    // MPI-only end
    MPI_Finalize();
    double prog1 = getTime();                    // total program end

    if (rank == 0) {
        double pi = h * global_sum;
        printf("pi is approximately %.16f, Error is %.16f\n", pi, pi - PI25DT);
        printf("Program time (incl. MPI_Init/Finalize): %.6f s\n", prog1 - prog0);
        printf("MPI-only time (excl. Init/Finalize):    %.6f s\n",  mpi1 - mpi0);
    }
    return 0;
}
