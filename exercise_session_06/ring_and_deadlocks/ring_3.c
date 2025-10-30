#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // --- build a 1D cartesian topology that is periodic (a ring)
    MPI_Comm comm_cart;
    const int ndims = 1;
    int dims[1]     = { world_size };  
    int periods[1]  = { 1 };           
    int reorder     = 0;               
    MPI_Cart_create(MPI_COMM_WORLD, ndims, dims, periods, reorder, &comm_cart);

    // From now on, use comm_cart (not MPI_COMM_WORLD)
    int rank, size;
    MPI_Comm_rank(comm_cart, &rank);
    MPI_Comm_size(comm_cart, &size);

    // get left (source) and right (dest) neighbors in the ring
    int src, dest;                     
    MPI_Cart_shift(comm_cart, /*direction=*/0, /*displ=*/1, &src, &dest);

    int my_sum   = 0;
    int send_val = rank;
    for (int it = 0; it < size; ++it) {
        int recv_val = -1;

        // simple, deadlock-free pairwise exchange
        MPI_Sendrecv(&send_val, 1, MPI_INT, dest, 0,
                     &recv_val, 1, MPI_INT, src,  0,
                     comm_cart, MPI_STATUS_IGNORE);

        my_sum  += recv_val;
        send_val = recv_val;
    }

    printf("I am process %d (of %d), sum = %d\n", rank, size, my_sum);

    MPI_Comm_free(&comm_cart);
    MPI_Finalize();
    return 0;
}
