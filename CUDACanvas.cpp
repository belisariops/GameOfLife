//
// Created by belisariops on 10/28/17.
//

#include "CUDACanvas.h"

extern void updateCuda(int *A, int *B, int height, int width) ;

CUDACanvas::CUDACanvas(int height, int width, int screenWidth, int screenHeight) : Canvas(height, width, screenWidth,
                                                                                          screenHeight) {}

void CUDACanvas::update() {
    //Call the .cu file
    updateCuda(currentGrid->values,nextGrid->values, currentGrid->getHeight(),currentGrid->getWidth());
}
