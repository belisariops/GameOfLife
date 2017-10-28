//
// Created by belisariops on 10/24/17.
//

#ifndef GAMEOFLIFE_CANVAS_H
#define GAMEOFLIFE_CANVAS_H


#include "Grid.h"

class Canvas {
public:
    Canvas(int height, int width, int screenWidth, int screenHeight);

    virtual ~Canvas();
    void setGrid(Grid *other);
    void draw();
    virtual void update() = 0;
private:
    int windowHeight;
    int windowWidth;
protected:
    Grid *currentGrid;
    Grid *nextGrid;
};


#endif //GAMEOFLIFE_CANVAS_H
