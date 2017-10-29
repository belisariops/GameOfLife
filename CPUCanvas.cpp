//
// Created by belisariops on 10/28/17.
//

#include "CPUCanvas.h"
#include "Utils.cpp"

CPUCanvas::CPUCanvas(int height, int width, int screenWidth, int screenHeight) : Canvas(height, width, screenWidth,
                                                                                        screenHeight) {}

/*Secuencial algorithm implementation*/
void CPUCanvas::update() {
    /*Every cell of the canvas is checked*/
    for (int h = 0; h < currentGrid->getHeight(); ++h) {
        for (int w = 0; w < currentGrid->getWidth(); ++w) {
            int aliveNeighbours = 0;
            /*The neighbours of the dead cell are checked*/
            for (int i = -1; i < 2; ++i) {
                for (int j = -1; j < 2; ++j) {
                    aliveNeighbours += (i | j ) && ( currentGrid->getValue(mod(h + i, currentGrid->getHeight()), mod(w + j, currentGrid->getWidth())));
                }
            }

            /*Set state of the cell in the next frame*/
            nextGrid->setValue(h,w,(currentGrid->getValue(h,w) == 0 && (aliveNeighbours == 3 || aliveNeighbours == 6))
                                || currentGrid->getValue(h,w) == 1 && (aliveNeighbours == 2 || aliveNeighbours == 3));


        }
    }

    /*The grid that is draw is updated*/
    delete(currentGrid);
    currentGrid = nextGrid;
    /*A new grid is created for the next iteration*/
    nextGrid = new Grid(currentGrid->getHeight(),currentGrid->getWidth());
}
