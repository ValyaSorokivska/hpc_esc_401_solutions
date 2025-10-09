#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "gettime.h"
#include <omp.h>  

typedef struct {
    float x;
    float y;
    float z;
    float r2;
} coord;

int main(int argc, char *argv[]) {
    (void)argc; (void)argv;   
    long N = (argc > 1) ? atol(argv[1]) : (long)1024*1024*64; 
    coord *data=malloc((size_t)N * sizeof(coord));
    int i;
    double sum;
    
    data = malloc(N * sizeof(coord));
    assert(data);

    double t0 = getTime();  
    
    sum = 0.0;
    #pragma omp parallel for reduction(+:sum)
    for(i=0; i<N; ++i) {
        data[i].x = i & 31;
        data[i].y = i & 63;
        data[i].z = i & 15;
        data[i].r2 = data[i].x*data[i].x + data[i].y*data[i].y + data[i].z*data[i].z;
        sum += sqrt(data[i].r2);
    }
    double t1 = getTime();    
    printf("sum=%.6f\n", sum);
    printf("Computed in %.6f seconds (N=%ld)\n", t1 - t0, N);

    free(data);
    return 0;
}
