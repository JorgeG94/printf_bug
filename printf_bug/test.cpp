#define HIP_ENABLE_PRINTF

#include <hip/hip_runtime.h>
#include <stdio.h>
#include "class.hpp"
#include <iostream>
#include "mpi.h"

int main() {

  
  //-- initialize return value for error handling --//
  int return_value = 0;
  //-- initialize MPI --//
  int init_res;
  init_res = MPI_Init(NULL, NULL);
  if (init_res != MPI_SUCCESS) {
    std::cout << "Fatal Error: MPI_Init failed!" << std::endl;

    return_value = 1;
    exit(return_value);
  }
  int world_rank;
  MPI_Comm world_comm = MPI_COMM_WORLD;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  program::hip_gpu::test object_test;

  hipDeviceSynchronize();
  object_test.test_print();
  hipDeviceSynchronize();

 //-- finalize MPI --//
  int final_res;
  final_res = MPI_Finalize();
  if (final_res != MPI_SUCCESS) {
    std::cout << "Fatal Error: MPI_Finalize failed!" << std::endl;
    return_value = 1;
  }

  hipDeviceSynchronize();
  return return_value;


}
