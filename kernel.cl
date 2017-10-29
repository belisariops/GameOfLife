int mod(int a, int b) {
    return a >= 0 ? a%b :  ( b - abs ( a%b ) ) % b;
}


kernel void update( global int* A, global int* B , global int* canvasDimensions) {
    const int index = get_global_id(0);
    int aliveNeighbours = 0;

    int h,w;
    h = index / canvasDimensions[1];
    w = index - (h * canvasDimensions[1]);

    /*The neighbours of the dead cell are checked*/
    for (int i = -1; i < 2; ++i) {
        for (int j = -1; j < 2; ++j) {
            aliveNeighbours += ( (i | j) && A[mod(h+i,canvasDimensions[0])*canvasDimensions[1] + mod(w+j,canvasDimensions[1])]);
        }
    }
    B[index] = (A[index] == 0 && (aliveNeighbours == 3 || aliveNeighbours == 6))
               || A[index] == 1 && (aliveNeighbours == 2 || aliveNeighbours == 3);
}