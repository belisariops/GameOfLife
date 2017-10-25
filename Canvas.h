//
// Created by belisariops on 10/24/17.
//

#ifndef GAMEOFLIFE_CANVAS_H
#define GAMEOFLIFE_CANVAS_H


#include "Grid.h"

class Canvas {
public:
    Canvas(int height, int width, int screenWidth, int screenHeight);
    ~Canvas();
    void setGrid(Grid *other);
    void update();
    void draw();
private:
    Grid *currentGrid;
    Grid *nextGrid;
    int windowHeight;
    int windowWidth;
};


#endif //GAMEOFLIFE_CANVAS_H
