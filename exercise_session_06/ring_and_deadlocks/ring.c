#include "mpi.h"
#include <stdio.h>

int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes and rank of the process
    int size, my_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    int send_first = (argc > 1) && 
                     (!strcmp(argv[1], "send-first") || !strcmp(argv[1], "sendfirst"));

    int my_sum = 0;

    int send_rank = my_rank;  // Send    buffer
    int recv_rank = 0;        // Receive buffer

    // Compute the ranks of left/right neighbours 
    int right_rank = (my_rank + 1) % size;
    int left_rank  = (my_rank - 1 + size) % size;

    // Loop over the number of property in ocesses
    //     send to right, receive from left
    //     update the send buffer
    //     update the local sum
    
    for (int iter = 0; iter < size; ++iter) {
        MPI_Request req[2];

        if (!send_first) {
            // Irecv -> Isend -> Waitall
            MPI_Irecv(&recv_rank, 1, MPI_INT, left_rank,  0, MPI_COMM_WORLD, &req[0]);
            MPI_Isend(&send_rank, 1, MPI_INT, right_rank, 0, MPI_COMM_WORLD, &req[1]);
        } else {
            // Isend -> Irecv -> Waitall
            MPI_Isend(&send_rank, 1, MPI_INT, right_rank, 0, MPI_COMM_WORLD, &req[0]);
            MPI_Irecv(&recv_rank, 1, MPI_INT, left_rank,  0, MPI_COMM_WORLD, &req[1]);
        }

        MPI_Waitall(2, req, MPI_STATUSES_IGNORE);

        my_sum   += recv_rank;   
        send_rank = recv_rank;   
    }


    printf("I am processor %d out of %d, and the sum is %d\n", my_rank, size, my_sum);

    // Finalize the MPI environment.
    MPI_Finalize();
    return 0;
}
