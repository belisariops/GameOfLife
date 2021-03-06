//
// Created by belisariops on 10/28/17.
//

#include <iostream>
#include "CUDACanvas.h"

extern void updateCuda(int *A, int *B, int height, int width) ;
extern void setUp(int heigt, int width);
extern void destroy();

CUDACanvas::CUDACanvas(int height, int width, int screenWidth, int screenHeight) : Canvas(height, width, screenWidth,
                                                                                          screenHeight) {
    setUp(height, width);
}

CUDACanvas ::~CUDACanvas() {
    destroy();
}

void CUDACanvas::update() {
    //Call the kernel wrapper

    updateCuda(currentGrid->values,nextGrid->values, currentGrid->getHeight(),currentGrid->getWidth());
    delete(currentGrid);
    currentGrid = nextGrid;
    /*A new grid is created for the next iteration*/
    nextGrid = new Grid(currentGrid->getHeight(),currentGrid->getWidth());
}
