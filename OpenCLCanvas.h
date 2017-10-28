//
// Created by belisariops on 10/28/17.
//

#ifndef GAMEOFLIFE_OPENCLCANVAS_H
#define GAMEOFLIFE_OPENCLCANVAS_H

#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <stdlib.h>

#define __CL_ENABLE_EXCEPTIONS
#ifdef __APPLE__
#include <OpenCL/cl.hpp>
#else
#include <CL/cl.hpp>
#endif

#include "Canvas.h"

class OpenCLCanvas : public Canvas {
public:
    OpenCLCanvas(int height, int width, int screenWidth, int screenHeight);
    ~OpenCLCanvas();
    void update();
private:
    int N_ELEMENTS;
    int platform_id=0;
    int device_id=0;
    cl::Kernel kernel;
    cl::Buffer bufferCurrentGrid;
    cl::Buffer bufferNextGrid;
    cl::CommandQueue queue;
};


#endif //GAMEOFLIFE_OPENCLCANVAS_H
