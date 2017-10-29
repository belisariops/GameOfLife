
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <device_launch_parameters.h>
#include <cuda_runtime_api.h>
#include <iostream>


__global__ void update(int *A, int *B, int h, int w) {
    const int index = blockIdx.x * blockDim.x + threadIdx.x;

    if (index < h*w)
        B[index] = A[index];
}

void updateCuda(int *A, int *B, int height, int width) {
    // Device input vectors
    int *d_a;
    //Device output vector
    int *d_b;

    // Size, in bytes, of each vector
    size_t bytes = height*width*sizeof(int);


    // Allocate memory for each vector on GPU
    cudaMalloc((void **) &d_a, bytes);
    cudaMalloc((void **) &d_b, bytes);

    // Copy host vectors to device
    cudaMemcpy(d_a, A, bytes, cudaMemcpyHostToDevice);

    int blockSize, gridSize, n;

    // Tamaño de la matriz.
    n = height*width;

    // Tamaño del bloque. Elegir entre 32 y 31.
    //blockSize = 32;
    blockSize = 32;

    // Number of thread blocks in grid
    gridSize = (int)ceil((float)n/blockSize);

    // Execute the kernel
    update<<< gridSize, blockSize >>>(d_b, d_a, height, width);

    // Copy array back to host
    cudaMemcpy( B, d_b, bytes, cudaMemcpyDeviceToHost );



    // Release device memory
    cudaFree(d_a);
    cudaFree(d_b);


}