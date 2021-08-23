# printf bug using hipcc

There are multiple files in this repo and a simple build script to build them all. You only need to load the rocm
module for correct compilation, the MPI path is the default one loaded when you log in. 

The simple.cpp file is the simplest implementatio of the printf that is similar to the program structure we use. This
involves a main function which build an object from a class that calls a function that calls another function that 
finally calls a GPU kernel. 

The wmpi.cpp is the same one expect with an MPI Init and Finalize, which is a part of the program.

nompi.cpp resembles the full structure of the code, the class is in a separate file and the kernels are in a separate file, 
however this file here has no mpi. 

test.cpp is the same as nompi.cpp except that it does contain an MPI Init and Finalize, just as the original code would.

simple.cpp and wmpi.cpp do not fail when run on an MI100 node. nompi.cpp and test.cpp do fail with the error 

`Memory access fault by GPU node-4 (Agent handle: 0x3dec5b0) on address (nil). Reason: Page not present or supervisor privilege.`

```
hipcc --offload-arch=gfx908 -fgpu-rdc  --gpu-max-threads-per-block=64 -I$MPI_ROOT/include -L$MPI_ROOT/lib -lmpi test.cpp class.cpp gpu.cpp -o multi

hipcc --offload-arch=gfx908 -fgpu-rdc  --gpu-max-threads-per-block=64 -I$MPI_ROOT/include -L$MPI_ROOT/lib -lmpi nompi.cpp class.cpp gpu.cpp -o nompi

hipcc --offload-arch=gfx908 -fgpu-rdc  --gpu-max-threads-per-block=64 -I$MPI_ROOT/include -L$MPI_ROOT/lib -lmpi wmpi.cpp -o mpi

hipcc --offload-arch=gfx908 -fgpu-rdc  --gpu-max-threads-per-block=64  simple.cpp -o simple
```
