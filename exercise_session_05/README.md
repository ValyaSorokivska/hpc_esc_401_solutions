Exercise 1
----------
Implementation of a serial 2D Poisson solver using the Jacobi iteration method.

I implemented the missing routines.

1. Function "init_f" initializes source term and boundary conditions.

2. Function "jacobi_step" updates grid values using the Jacobi formula.

3. Function "norm_diff" computes L² difference between two iterations.

Visualized results can be found in file test.png. The results show correct boundary diffusion for rhs_function = 2.

Files:
init.cpp, jacobi.cpp, io.cpp, main.cpp, params.txt, Makefile, output/plot.py

Exercise 2
----------
Parallelization of the Jacobi solver with OpenMP.

I  copied the serial version and updated the Makefile to include -fopenmp.
Added OpenMP directives to jacobi_step and norm_diff using #pragma omp parallel for collapse and reduction.
Also ran tests with 1 and 4 threads (OMP_NUM_THREADS). It gave me same numerical result, but with the faster runtime.
It produced run_1t.log and run_4t.log for comparison.

Files:
Makefile, jacobi.cpp (updated with OpenMP), run_1t.log, run_4t.log, test.png

Exercise 3
----------
Parallelization of a simple code that computes the maximum value and counts zeros in an integer array (num.txt).

First, I added #pragma omp parallel for to both loops, which caused race conditions and gave wrong results (161430 zeros instead of 646016).
Then I fixed the issue using OpenMP reductions:

1. reduction(max:maxval) for finding the maximum

2. reduction(+:num_n0) for counting zeros

Results with 1 and 4 threads are identical to the serial version (max=38747, zeros=646016).
Timing: both versions run in about 0:00.04 s.

Files:
serial.c, omp_racy.c, num.txt, race_serial, race_omp, race_racy
