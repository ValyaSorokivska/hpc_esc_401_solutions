Exercise 1
------------
The output:
PI = 3.141592653589793 computed in 3.296 seconds 
PI = 3.141592653589793 computed in 0.00115 seconds 
PI = 3.141592653589793 computed in 0.001142 seconds 
PI = 3.141592653589793 computed in 0.001141 seconds
PI = 3.141592653589793 computed in 0.001145 seconds

Serial run: 3.296 seconds
OpenACC runs: 0.00114 seconds each

The serial version executes the full loop and because of the high number  of iterations, it  takes seconds.

The OpenACC version uses the GPU, which has thousands of parallel cores.
The loop iterations are independent  and the GPU can compute them simultaneously.
The four OpenACC runs have very similar (almost identical) runtimes.

File: cpi_openacc.c

Exercise 2
------------
The output:
PI = 3.14159265358979 computed in 0.04855 seconds
Compared to the serial CPU code thatruns for 3.3 seconds this gives a speedup 
The GPU already makes the computation much faster.
But the CUDA code is still much slower than the OpenACC version that runs ~0.00114 seconds
So the given CUDA implementation is not fully optimized (the next one is).

Exercise 3 
-------------
Fix blocks, increase threads:
Runtime drops a lot when we go from few threads (16) to more (64–160),
BUT  the improvement becomes smaller and eventually negligible.

Fix threads, increase blocks:
Has the same effect and after 300 blocks the runtime does not improve significantly,
sometimes it can get worse.

So in conclusion, the increase of blocks and threads gives more parallelism,
BUT when  there is enough blocks/threads to keep all cores busy, new blocks/threads will only slow the process. 

Output:
60:
---
B=60 T=16 : PI = 3.141592653589794 computed in 0.09125 seconds
B=60 T=32 : PI = 3.141592653589793 computed in 0.04567 seconds
B=60 T=48 : PI = 3.141592653589794 computed in 0.03056 seconds
B=60 T=64 : PI = 3.141592653589792 computed in 0.02292 seconds
B=60 T=80 : PI = 3.141592653589793 computed in 0.01841 seconds
B=60 T=96 : PI = 3.141592653589796 computed in 0.01536 seconds
B=60 T=112 : PI = 3.141592653589795 computed in 0.01309 seconds
B=60 T=128 : PI = 3.1415926535898 computed in 0.01162 seconds
B=60 T=144 : PI = 3.141592653589793 computed in 0.01051 seconds
B=60 T=160 : PI = 3.141592653589789 computed in 0.009568 seconds

120:
---
B=120 T=16 : PI = 3.141592653589793 computed in 0.04531 seconds
B=120 T=32 : PI = 3.141592653589792 computed in 0.02275 seconds
B=120 T=48 : PI = 3.141592653589796 computed in 0.01523 seconds
B=120 T=64 : PI = 3.1415926535898 computed in 0.01147 seconds
B=120 T=80 : PI = 3.141592653589789 computed in 0.009213 seconds
B=120 T=96 : PI = 3.141592653589788 computed in 0.00776 seconds
B=120 T=112 : PI = 3.141592653589794 computed in 0.006625 seconds
B=120 T=128 : PI = 3.141592653589795 computed in 0.006181 seconds
B=120 T=144 : PI = 3.141592653589794 computed in 0.006362 seconds
B=120 T=160 : PI = 3.141592653589796 computed in 0.006069 seconds

180:
----
B=180 T=16 : PI = 3.141592653589794 computed in 0.0305 seconds
B=180 T=32 : PI = 3.141592653589796 computed in 0.01533 seconds
B=180 T=48 : PI = 3.141592653589793 computed in 0.01028 seconds
B=180 T=64 : PI = 3.141592653589788 computed in 0.007743 seconds
B=180 T=80 : PI = 3.141592653589795 computed in 0.006503 seconds
B=180 T=96 : PI = 3.141592653589794 computed in 0.005865 seconds
B=180 T=112 : PI = 3.141592653589796 computed in 0.005069 seconds
B=180 T=128 : PI = 3.141592653589796 computed in 0.01375 seconds
B=180 T=144 : PI = 3.141592653589803 computed in 0.004351 seconds
B=180 T=160 : PI = 3.141592653589794 computed in 0.004016 seconds

240:
----
B=240 T=16 : PI = 3.141592653589792 computed in 0.02291 seconds
B=240 T=32 : PI = 3.1415926535898 computed in 0.01154 seconds
B=240 T=48 : PI = 3.141592653589788 computed in 0.007749 seconds
B=240 T=64 : PI = 3.141592653589795 computed in 0.006075 seconds
B=240 T=80 : PI = 3.141592653589796 computed in 0.006151 seconds
B=240 T=96 : PI = 3.141592653589796 computed in 0.004454 seconds
B=240 T=112 : PI = 3.141592653589791 computed in 0.004695 seconds
B=240 T=128 : PI = 3.141592653589798 computed in 0.003689 seconds
B=240 T=144 : PI = 3.141592653589796 computed in 0.003643 seconds
B=240 T=160 : PI = 3.141592653589797 computed in 0.003372 seconds

300:
---
B=300 T=16 : PI = 3.141592653589793 computed in 0.01837 seconds
B=300 T=32 : PI = 3.141592653589789 computed in 0.009302 seconds
B=300 T=48 : PI = 3.141592653589795 computed in 0.006433 seconds
B=300 T=64 : PI = 3.141592653589796 computed in 0.005277 seconds
B=300 T=80 : PI = 3.141592653589791 computed in 0.00525 seconds
B=300 T=96 : PI = 3.141592653589794 computed in 0.004049 seconds
B=300 T=112 : PI = 3.141592653589792 computed in 0.003725 seconds
B=300 T=128 : PI = 3.141592653589797 computed in 0.003395 seconds
B=300 T=144 : PI = 3.141592653589798 computed in 0.004023 seconds
B=300 T=160 : PI = 3.141592653589788 computed in 0.003171 seconds

360:
---
B=360 T=16 : PI = 3.141592653589796 computed in 0.01531 seconds
B=360 T=32 : PI = 3.141592653589788 computed in 0.007694 seconds
B=360 T=48 : PI = 3.141592653589794 computed in 0.005779 seconds
B=360 T=64 : PI = 3.141592653589796 computed in 0.004476 seconds
B=360 T=80 : PI = 3.141592653589794 computed in 0.003955 seconds
B=360 T=96 : PI = 3.141592653589796 computed in 0.00363 seconds
B=360 T=112 : PI = 3.141592653589794 computed in 0.003279 seconds
B=360 T=128 : PI = 3.141592653589793 computed in 0.003156 seconds
B=360 T=144 : PI = 3.141592653589798 computed in 0.00388 seconds
B=360 T=160 : PI = 3.141592653589796 computed in 0.003267 seconds

420:
---
B=420 T=16 : PI = 3.141592653589795 computed in 0.01316 seconds
B=420 T=32 : PI = 3.141592653589794 computed in 0.006634 seconds
B=420 T=48 : PI = 3.141592653589796 computed in 0.005606 seconds
B=420 T=64 : PI = 3.141592653589791 computed in 0.004679 seconds
B=420 T=80 : PI = 3.141592653589792 computed in 0.003723 seconds
B=420 T=96 : PI = 3.141592653589794 computed in 0.003252 seconds
B=420 T=112 : PI = 3.141592653589751 computed in 0.003215 seconds
B=420 T=128 : PI = 3.14159265358979 computed in 0.003141 seconds
B=420 T=144 : PI = 3.141592653589798 computed in 0.003315 seconds
B=420 T=160 : PI = 3.141592653589807 computed in 0.003273 seconds

600:
---
B=600 T=16 : PI = 3.141592653589789 computed in 0.009686 seconds
B=600 T=32 : PI = 3.141592653589796 computed in 0.006144 seconds
B=600 T=48 : PI = 3.141592653589794 computed in 0.004924 seconds
B=600 T=64 : PI = 3.141592653589797 computed in 0.003367 seconds
B=600 T=80 : PI = 3.141592653589788 computed in 0.003181 seconds
B=600 T=96 : PI = 3.141592653589796 computed in 0.003266 seconds
B=600 T=112 : PI = 3.141592653589807 computed in 0.003294 seconds
B=600 T=128 : PI = 3.141592653589801 computed in 0.003314 seconds
B=600 T=144 : PI = 3.1415926535898 computed in 0.003687 seconds
B=600 T=160 : PI = 3.141592653589786 computed in 0.003926 seconds

Files:cpi_cuda.cu, test.sh
