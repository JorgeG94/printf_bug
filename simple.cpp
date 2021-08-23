#define HIP_ENABLE_PRINTF

#include <hip/hip_runtime.h>
#include <stdio.h>
//#include "class.hpp"
//#include <iostream>
//#include "mpi.h"

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


  exess::hip_gpu::test object_test;

  object_test.test_print();

  return 1;


}
