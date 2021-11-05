# Build

```
module load rocm
hipcc -L$ROCM_PATH/lib -lhipblas dgemm.cpp
hipcc -L$ROCM_PATH/lib -lrocblas rocblas_dgemm.cpp
```
rocm 4.2.0 timing: 7.296 seconds
rocm 4.3.1 timing: 10.96 seconds
rocm 4.4.0 timing: 11.35 seconds
