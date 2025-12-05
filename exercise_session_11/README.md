First Exercise
---------------

Almost all the time is spent inside main, in nbody.cpp lines 38–40. 
Those lines are exactly the inner part of your forces() routine (from the code):

	    ax += dx * ir3;
	    ay += dy * ir3;
	    az += dz * ir3;


From the report:
2.3% |    29.0 | line.38
4|||  21.2% |   267.0 | line.39
4|||  57.6% |   724.0 | line.40

It happens because the algorithm performs O(n²) pairwise interactions (every particle interacts with every other one). 
The expensive operations inside this loop—especially the sqrt()—dominate the runtime.
The remaining samples come from accessing elements of std::vector.

Therefore the computation is compute-bound, not memory-bound. 
Any meaningful optimization must therefore focus on the inner force loop.


File: report.txt

Exercise 2
---------------
time ./nbody with sqrt:

real	0m12,725s
user	0m12,709s
sys	0m0,001s


time ./nbody with sqrtf:

real	0m7,153s
user	0m7,145s
sys	0m0,005s

Initially the code used sqrt on float data. 
Sqrt is the double version. The compiler promotes the argument to double, does a double-precision sqrt, then casts back to float.
Sqrtf works directly in float, so you avoid unnecessary type conversions and an expensive double-precision operation.
Measured runtimes:
sqrt: 12.7 s
sqrtf: 7.1 s
This corresponds to about 1.8× speed-up.
The numerical results remain  the same, but performance improves because the inner loop does less work per interaction.

File: nbody.cpp 

Exercise 3
---------------
For the first output yhe compiler cannot vectorise the main force loop with the current data layout.

time ./nbody

real	0m7,070s
user	0m7,059s
sys	0m0,009s

Change: I replaced the original array-of-structures layout
(vector<particle> plist) with a structure-of-arrays layout
(struct particles { vector<float> x, y, z, vx, vy, vz, ax, ay, az; };).
The force loop now works on separate x, y, z arrays instead of plist[i].x.

With SoA, x[i], x[j] etc. are contiguous, so the compiler can vectorize the loop over j.
The SoA version runs faster than the original AoS version because memory access is more cache-friendly (contiguous arrays) and SIMD units can be used on dx, dy, dz computations inside the inner loop.
However, for N = 50 000 I measured almost identical runtimes (~7.1 s) before and after the change. The kernel is dominated by expensive floating-point operations in the O(N²) interaction loop, so improvements have only a very small impact on the total execution time in this setup.
To be honest, I expected that it would be faster than that.

File:nbody.cpp

Exercise 4
---------------
time ./nbody

real	0m1,553s
user	0m1,522s
sys	0m0,005s

if inside the inner loop caused divergence and made vectorization harder.
I rewrote it as two loops without the branch:
for (int j = 0; j < i; ++j) { ... }
for (int j = i+1; j < n; ++j) { ... }

So we still skip j = i, but there is no conditional inside the loop body.

Timing with time ./nbody shows a better runtime than before.

File: nbody.cpp

Exercise 5
----------------
export OMP_NUM_THREADS=128
time ./nbody

real	0m1,994s
user	3m12,786s
sys	0m0,545s

For N = 500,000 and 128 OpenMP threads, the runtime is about 2 seconds.

User time measures the total CPU time summed over all threads.
Since the N-body code runs with 128 OpenMP threads, each thread contributes its own CPU time. 
Although the real wall-clock time is only ~2 seconds, the user time is ~193 seconds, corresponding to about 96 threads running at full capacity.
This indicates good parallel utilization and is expected behavior for parallel OpenMP programs.

The user time indicates ~96 core-seconds used per second of wall time, corresponding to roughly 75% parallel efficiency. 
This is very good given the 𝑂(𝑁^2) computational cost and the overhead of square-root and memory accesses.

File: nbody.cpp



