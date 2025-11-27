Exercise 1
-----------
Loaded necessary modules and used srun to allocate and run code on a GPU node.
File: a.out

Exercise 2
----------
Implemented 1D Indexing and configured the kernel with a 1D grid launch.
File:a.out

Exercise 3
------------
Extended parallel processing to handle n_x* n_y matrices.
Used 2D Indexing with .x and .y variables, converted 2D coordinates to a Linear Index.
File:a.out

Exercise 4
-----------
Implemented a 2D stencil operation.
Implemented Neighbor Indexing (for convolution). 
The Optimal Block Size is: 128

the output for different sizes of blocks:

128:

Convolution took  0.063616 sec. on GPU
Convolution took  0.004813 sec. on CPU

256:

Convolution took  0.065360 sec. on GPU
Convolution took  0.004808 sec. on CPU

512:
Convolution took  0.064246 sec. on GPU
Convolution took  0.004840 sec. on CPU


Files: 	convol.o
