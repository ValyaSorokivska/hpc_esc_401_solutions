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

Exercise 2
------------
The output:
PI = 3.14159265358979 computed in 0.04855 seconds



Exercise 3 
-------------
