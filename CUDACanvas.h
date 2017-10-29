//
// Created by belisariops on 10/28/17.
//

#ifndef GAMEOFLIFE_CUDACANVAS_H
#define GAMEOFLIFE_CUDACANVAS_H


#include "Canvas.h"

class CUDACanvas : public Canvas {
public:
    CUDACanvas(int height, int width, int screenWidth, int screenHeight);
    void update();
};


#endif //GAMEOFLIFE_CUDACANVAS_H
