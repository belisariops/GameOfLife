kernel void update( global int* A, global int* B ) {
    const int idx = get_global_id(0);
    B[idx] = A[idx];
}