Exercise 1
----------
Created the cowsay image.
The serial Poisson solver was compiled and executed on an Ubuntu virtual machine using g++ and make. 
The generated output files are visualized using a Python script (the image test.png) 

File: poisson_solver_serial/*, cowsay.png

Exercise 1, bonus part 
----------------------
Bonus Task – Parallel Poisson Solver (OpenMP & MPI)

Parallel versions of the Poisson solver were compiled and executed using OpenMP and MPI.
Performance data were collected and visualized using a Python script, producing a speedup plot.

In the MPI version, the solver was compiled with mpic++ and executed with multiple MPI ranks. 
For postprocessing, I renamed the rank-0 output files to match the expected naming convention of the provided plotting script. Then I visualize the results.

Files: output folders, changes to Makefiles 

Exercise 2 
-----------

I created  the docker image of the serial Poisson solver  using a Dockerfile. 
The image installs the required build tools (g++, make), copies the source code, compiles the solver, and runs it at container startup.
The container was executed locally and on the Science Cloud VM. 

I pushed the image to Docker Hub and pulled on the VM.

File: Dockerfile

