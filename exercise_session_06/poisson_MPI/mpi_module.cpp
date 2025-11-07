#include "mpi.h"
#include <stdio.h>
#include "init.h"
#include <vector>


int start_MPI(int* my_rank, int* size){
	printf("Setting MPI environment\n");
	MPI_Init(NULL,NULL);
	MPI_Comm_size(MPI_COMM_WORLD,size);
	MPI_Comm_rank(MPI_COMM_WORLD,my_rank);

	return 0;
}

int close_MPI(){
	MPI_Finalize();
	return 0;
}

int mpi_get_domain(int nx, int ny, int my_rank, int size, int* min_x, int* max_x, int* min_y, int* max_y){
	const int q = nx / size;      
    const int r = nx % size;       

    const int nx_loc = q + (my_rank < r ? 1 : 0);

    int x0;
    if (my_rank < r) {
        x0 = my_rank * (q + 1);
    } else {
        x0 = r * (q + 1) + (my_rank - r) * q;
    }
    const int x1 = x0 + nx_loc;    

    *min_x = x0;        
    *max_x = x0 + nx_loc;
    *min_y = 0;        
    *max_y = ny;
	
	printf("I am rank %d and my domain is: xmin, xmax, ymin, ymax: %d %d %d %d\n",my_rank,*min_x,*max_x,*min_y,*max_y);
	return 0;
}

int halo_comm(params p, int my_rank, int size, double** u, double* fromLeft, double* fromRight){
	
	const int nx_loc = p.xmax - p.xmin;   // number of local columns
    const int ny_loc = p.ymax - p.ymin;   // number of local rows

    const int left  = (my_rank > 0)        ? my_rank - 1 : MPI_PROC_NULL;
    const int right = (my_rank < size - 1) ? my_rank + 1 : MPI_PROC_NULL;
    
	for (int j = 0; j < ny_loc; ++j) {
		fromLeft[j] = 0.0; fromRight[j] = 0.0; 
	}

	
 	double* sendL = new double[ny_loc];
    double* sendR = new double[ny_loc];
	
    for (int j = 0; j < ny_loc; ++j) {
        sendL[j] = u[0][j];               // send first interior col to left neighbor
        sendR[j] = u[nx_loc - 1][j];      // send last  interior col to right neighbor
    }

    //non-blocking exchange 
    MPI_Request req[4]; int k = 0;

    // receive halos 
    MPI_Irecv(fromLeft,  ny_loc, MPI_DOUBLE, left,  11, MPI_COMM_WORLD, &req[k++]);  // from lefft  neighbor
    MPI_Irecv(fromRight, ny_loc, MPI_DOUBLE, right, 10, MPI_COMM_WORLD, &req[k++]);  // from rigt neighbor

    // send columns
    MPI_Isend(sendL, ny_loc, MPI_DOUBLE, left,  10, MPI_COMM_WORLD, &req[k++]); 
    MPI_Isend(sendR, ny_loc, MPI_DOUBLE, right, 11, MPI_COMM_WORLD, &req[k++]); 

    MPI_Waitall(k, req, MPI_STATUSES_IGNORE);

    return 0;
}


int ALLREDUCE(double* loc_diff, double* loc_sumdiff){

	MPI_Allreduce(loc_diff, loc_sumdiff, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
	return 0;

	}

