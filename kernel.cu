

#include <device_launch_parameters.h>
#include <cuda_runtime_api.h>
// Device input vectors
int *d_a;
//Device output vector
int *d_b;

__device__ int mod(int a, int b) {
    return a >= 0 ? a%b :  ( b - abs ( a%b ) ) % b;
}


__global__ void update(int *A, int *B, int height, int width) {
    const int index = blockIdx.x * blockDim.x + threadIdx.x;

    if (index < height*width) {
        int aliveNeighbours = 0;


        const int h = index / width;
        const int w = index % width;

        /*The neighbours of the cell are checked*/
        for (int i = -1; i < 2; ++i) {
            for (int j = -1; j < 2; ++j) {
                aliveNeighbours +=  ( (i | j) && A[mod(h+i,height)*width + mod(w+j,width)]);
            }
        }
        B[index] = (A[index] == 0 && (aliveNeighbours == 3 || aliveNeighbours == 6))
                   || A[index] == 1 && (aliveNeighbours == 2 || aliveNeighbours == 3);
    }
}

void setUp(int height, int width) {
    // Allocate memory for each vector on GPU
    cudaMalloc((void **) &d_a, width*height);
    cudaMalloc((void **) &d_b, width*height);
}

void destroy() {
    // Release device memory
    cudaFree(d_a);
    cudaFree(d_b);
}

void updateCuda(int *A, int *B, int height, int width) {


    // Size, in bytes, of each vector
    size_t bytes = height*width*sizeof(int);


    // Copy host vectors to device
    cudaMemcpy(d_a, A, bytes, cudaMemcpyHostToDevice);


    int blockSize, gridSize, n;

//    // Tamaño de la matriz.
//    n = height*width;
//
//    // Tamaño del bloque. Elegir entre 32 y 31.
//    //blockSize = 32;
//    blockSize = 32;
//
//    // Number of thread blocks in grid
//    gridSize = (int)ceil((float)n/blockSize);

    // Execute the kernel
    update<<< width*height, 1 >>>(d_a, d_b, height, width);

    // Copy array back to host
    cudaMemcpy( B, d_b, bytes, cudaMemcpyDeviceToHost );




}