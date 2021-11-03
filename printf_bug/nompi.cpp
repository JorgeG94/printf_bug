#define HIP_ENABLE_PRINTF

#include <hip/hip_runtime.h>
#include <stdio.h>
#include "class.hpp"
#include <iostream>

int main() {

  

  program::hip_gpu::test object_test;

  hipDeviceSynchronize();
  object_test.test_print();
  hipDeviceSynchronize();


  hipDeviceSynchronize();
  return 1;


}
