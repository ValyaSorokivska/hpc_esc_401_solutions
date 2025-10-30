#include <mpi.h>
#include <stdio.h>

static inline double ref_pi(void) { return 3.14159265358979323846; }

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    long long N = (argc > 1) ? atoll(argv[1]) : 100000000LL;

    long long base = N / size;
    long long rem  = N % size;
    long long count = base + (rank < rem);
    long long start = rank * base + (rank < rem ? rank : rem);
    long long end   = start + count;  

    double t0 = MPI_Wtime();

    double local = 0.0;
    for (long long i = start; i < end; ++i) {
        double s = (i & 1) ? -1.0 : 1.0;   // (-1)^i
        local += s / (2.0 * (double)i + 1.0);
    }

    double global = 0.0;
    MPI_Reduce(&local, &global, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    double t1 = MPI_Wtime();

    if (rank == 0) {
        double pi = 4.0 * global;
        double err = pi - ref_pi();
        printf("N = %lld terms, ranks = %d\n", N, size);
        printf("pi ≈ %.15f  (error = %+ .3e)\n", pi, err);
        printf("time = %.3f s\n", t1 - t0);
    }

    MPI_Finalize();
    return 0;
}
