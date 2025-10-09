Exercise 1
----------

Program time is 0.105874 s. MPI-only time is 0.037864 s.

Starting and stopping MPI has a cost. The program time includes that setup but the MPI-only time doesn’t, so it’s smaller. On short runs, this overhead is a big fraction and on longer runs it becomes relatively small.

Exercise 2
----------
I measured time using function getTime() and in the script  sum.c I  changed prints to sum=..  and Computed .. in seconds. I  tried different optimization flags -O0/-O1/-O2/-O3. The results are in  the files run_sum_number.txt. With  0 I saw no optimazation, with 02/03 it was faster.  To make it even more faster I can try -ffast-math. The results are following:

0 ---- 0.911196 seconds;
1 ---- 0.366357 seconds;
2 ---- 0.200816 seconds;
3 ---- 0.202917 seconds.


For OpenMP I inserted #pragma omp parallel for reduction(+:sum) before the loop. It runs with various threads, I tried with 1,  4 and 8. Results are in the files run_sum_omp_tnumber.txt. I compiled it with cc -O3 -fopenmp -o sum_omp sum.c gettime.o -lm

The plot in  speedup.png shows how the runtime of the OpenMP version increases with the bigger number of threads. It coresponds to:

1 thread ---- 0.203174 seconds;
2 threads --- 0.052893 seconds;
8 threads --- 0.018092 seconds.

So OpenMP parallelization significantly reduces runtime compared to the serial version, especially for 2–8 threads.

Exercise 3
----------
When the program runs on  several processors, sometimes it becomes faster than expected, faster than linear speedup. In this case the speedup is called superlinear.

It happens because each processor works on a smaller part of the data and it makes memory access faster. Using several CPUs can also increase total memory bandwidth. Also parallel  version might avoid inefficiencies. So the harware is used more efficiently in parallel.

