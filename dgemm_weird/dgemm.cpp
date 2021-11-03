#include <hip/hip_runtime.h>
#include <hipblas.h>
#include <iostream>
#include <iomanip>
#include <chrono>


int main(){

const double m_S_evec[49] =
    {0.195014,  -0.696516, -0.110288, 0.237922,  -0.153390, 0.445773,
     0.431072,  -0.003086, 0.008834,  -0.176322, 0.273134,  0.526744,
     0.549541,  -0.561041, -0.709064, 0.265496,  -0.218803, 0.474760,
     -0.324154, 0.155324,  0.155777,  -0.000008, -0.000011, -0.889370,
     -0.452840, -0.062903, 0.000004,  -0.000005, 0.640058,  0.299327,
     -0.241843, 0.524628,  -0.357574, -0.139785, -0.140030, 0.000376,
     0.000716,  -0.225301, 0.349966,  0.666008,  -0.436685, 0.438751,
     -0.222518, -0.595569, -0.092976, 0.201544,  -0.136213, -0.514716,
     -0.512867};
const double m_S_eval[49] = {
        1.638218, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000,
        0.000000, 1.496663, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000,
        0.000000, 0.000000, 1.059941, 0.000000, 0.000000, 0.000000, 0.000000,
        0.000000, 0.000000, 0.000000, 1.000002, 0.000000, 0.000000, 0.000000,
        0.000000, 0.000000, 0.000000, 0.000000, 0.958048, 0.000000, 0.000000,
        0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.862609, 0.000000,
        0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.733740};

	// set device 
	hipSetDevice(0);
	//create handles 
	hipblasHandle_t blas_handle;
	hipblasCreate(&blas_handle);


	// number of basis functions in STO-3G w1
	int n = 7;
	int nn = n*n;

	double *A;
	double *B;
	double *C;

	double *d_A;
	double *d_B;
	double *d_C;

	double zero[1] = {0.0};
	double one[1] = {0.0};

	// host based mallocs
	hipHostMalloc((void**) &A, nn*sizeof(double));
	hipHostMalloc((void**) &B, nn*sizeof(double));
	hipHostMalloc((void**) &C, nn*sizeof(double));

	
	// copy matrices 
	for(int i = 0; i < nn; ++i){
		A[i] = m_S_evec[i];
		B[i] = m_S_eval[i];
	}	

	// device mallocs
	hipMalloc((void**) &d_A, nn*sizeof(double));
	hipMalloc((void**) &d_B, nn*sizeof(double));
	hipMalloc((void**) &d_C, nn*sizeof(double));

	// memset device matrices
	hipMemset(d_A, 0.0, nn & sizeof(double));
	hipMemset(d_B, 0.0, nn & sizeof(double));
	hipMemset(d_C, 0.0, nn & sizeof(double));

	// copy A and B into device pointers
	hipMemcpy(d_A, A, nn*sizeof(double), hipMemcpyHostToDevice);
	hipMemcpy(d_B, B, nn*sizeof(double), hipMemcpyHostToDevice);


	// start timers 
	auto start = std::chrono::high_resolution_clock::now();
	//dgemm
	hipblasStatus_t hipblas_status;
	hipblas_status = hipblasDgemm(blas_handle, HIPBLAS_OP_N, HIPBLAS_OP_N,
																n, n, n, one, d_A, n, d_B, n, zero, d_C, n);

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> diff = end - start;
	std::cout << "time for dgemm (s) " 
						<< std::setprecision(4) << 0.001 * diff.count() 
						<< std::endl;
	

	
	hipFree(d_A);
	hipFree(d_B);
	hipFree(d_C);
	hipHostFree(A);
	hipHostFree(B);
	hipHostFree(C);

	hipblasDestroy(blas_handle);

}
