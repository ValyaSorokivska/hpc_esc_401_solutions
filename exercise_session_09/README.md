Exercise 1
-----------
Output:
16:
memcopy and daxpy test of size 65536

timings:
1. axpy (openmp): 0.0622288 s
2. axpy (openacc): 2.82393 s

20:
memcopy and daxpy test of size 1048576

timings:
1. axpy (openmp): 0.0623379 s
2. axpy (openacc): 2.85067 s

24:
memcopy and daxpy test of size 16777216

timings:
1. axpy (openmp): 0.0643471 s
2. axpy (openacc): 3.36821 s

The GPU version is much slower that CPU version.
It happens because there is little computation per element, a big fixed overhead for GPU and CPU is already efficient

Files:axpy.openacc, axpy_openacc.cpp


Exercise 2
-----------
Output for naive version:
20:
dispersion 1D test of length n = 1048580 : 8.00003MB
Host version took 0.16417 s (0.0016417 s/step)
GPU version took 3.66832 s (0.0366832 s/step)

18:
dispersion 1D test of length n = 262148 : 2.00003MB
Host version took 0.14333 s (0.0014333 s/step)
GPU version took 2.86377 s (0.0286377 s/step)

22:
dispersion 1D test of length n = 4194308 : 32MB
Host version took 0.14929 s (0.0014929 s/step)
GPU version took 3.58217 s (0.0358217 s/step)

1)The naive OpenACC blur implementation is much slower than the CPU version because every iteration performs expensive data transfers between host and device. 
The GPU spends almost all of its time waiting for memory movement rather than computing, so increasing the problem size does not significantly change performance.

Output for blur_twice_gpu_nocopies:
20:
dispersion 1D test of length n = 1048580 : 8.00003MB
Host version took 0.218382 s (0.00218382 s/step)
GPU version took 2.85706 s (0.0285706 s/step)

18:
dispersion 1D test of length n = 262148 : 2.00003MB
Host version took 0.137059 s (0.00137059 s/step)
GPU version took 2.83548 s (0.0283548 s/step)

22:
dispersion 1D test of length n = 4194308 : 32MB
Host version took 0.149569 s (0.00149569 s/step)
GPU version took 2.83995 s (0.0283995 s/step)

2) blur_twice_gpu_nocopies does the same , but it opens one long #pragma acc data region around the whole nsteps loop.
The arrays are copied once to the GPU at the beginning and once back at the end.
The temporary buffer is never moved.
All three loops run on the device within that single data region.

So the difference is that in naive we have many small GPU regions and in nocopies: one big GPU region (the data kept on the device)

3) The GPU version is slower than the CPU OpenMP version in this problem.
Here the runtime is dominated by kernel launch overhead and OpenACC runtime overhead, not by the actual arithmetic.
The CPU time per step scales better with N, but  the CPU still finishes faster.

Files:blur_openacc.cpp,  blur.openacc, 

Exercise 3 
-----------

Output:
24:
dot product OpenACC of length n = 16777216 : 128MB
Host kernel took 0.0630278 s
GPU kernel took 3.38554 s

1)n the dot product all threads update the same variable sum inside the loop.
If we parallelise the loop, multiple threads can read, modify and write sum at the same time, so some updates get lost.

2)reduction(+:sum); It gives each thread a private copy of sum and combines them at the end.

3)For small vector sizes the GPU is slower, because of the overhead for the tiny amount of work per element.
For large vectors the GPU performance gets closer to the CPU version.
The parallel dot product becomes bandwidth-bound and the many GPU threads are fully utilised.


Files: dot_openacc.cpp, dot.openacc.




