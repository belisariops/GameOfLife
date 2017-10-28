//
// Created by belisariops on 10/28/17.
//

#ifndef GAMEOFLIFE_CPUCANVAS_H
#define GAMEOFLIFE_CPUCANVAS_H


#include "Canvas.h"

class CPUCanvas : public Canvas{
public:
    CPUCanvas(int height, int width, int screenWidth, int screenHeight);
    void update();

};


#endif //GAMEOFLIFE_CPUCANVAS_H
