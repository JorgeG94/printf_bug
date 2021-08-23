#define HIP_ENABLE_PRINTF

#include <hip/hip_runtime.h>
#include <stdio.h>
#include <iostream>
#include "mpi.h"

namespace exess{
namespace hip_gpu{
__global__ void run_printf() { 
printf("Hello World\n"); 
}

extern "C" void call_print(){

    int device_count = 0;
    hipGetDeviceCount(&device_count);
    for (int i = 0; i < device_count; ++i) {
        hipSetDevice(i);
        hipLaunchKernelGGL(HIP_KERNEL_NAME(run_printf), dim3(1), dim3(1), 0, 0);
        hipDeviceSynchronize();
    }


}

void just_print(){
  call_print();
}


class test{


  public:
  void test_print(){
    just_print();
  }


};
}
}

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

  exess::hip_gpu::test object_test;

  object_test.test_print();

 //-- finalize MPI --//
  int final_res;
  final_res = MPI_Finalize();
  if (final_res != MPI_SUCCESS) {
    std::cout << "Fatal Error: MPI_Finalize failed!" << std::endl;
    return_value = 1;
  }
  return return_value;


}
