#!/bin/bash

module load rocm
export MPI_ROOT=/opt/cray/pe/mpich/8.1.7/ofi/crayclang/10.0

rm mpi
rm multi
rm simple
rm nompi 

hipcc --offload-arch=gfx908 -fgpu-rdc  --gpu-max-threads-per-block=64 -I$MPI_ROOT/include -L$MPI_ROOT/lib -lmpi test.cpp class.cpp gpu.cpp -o multi

hipcc --offload-arch=gfx908 -fgpu-rdc  --gpu-max-threads-per-block=64 -I$MPI_ROOT/include -L$MPI_ROOT/lib -lmpi nompi.cpp class.cpp gpu.cpp -o nompi

hipcc --offload-arch=gfx908 -fgpu-rdc  --gpu-max-threads-per-block=64 -I$MPI_ROOT/include -L$MPI_ROOT/lib -lmpi wmpi.cpp -o mpi

hipcc --offload-arch=gfx908 -fgpu-rdc  --gpu-max-threads-per-block=64  simple.cpp -o simple
