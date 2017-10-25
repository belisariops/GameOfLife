//
// Created by belisariops on 10/24/17.
//

#include "Canvas.h"
#include "Window.h"
#include "Utils.cpp"

Canvas::Canvas(int height, int width, int screenHeight, int screenWidth) {
    currentGrid = new Grid(height, width);
    currentGrid->loadFromFile("replicator");
    nextGrid = new Grid(height,width);
    windowHeight = screenHeight;
    windowWidth = screenWidth;
}

Canvas::~Canvas() {
    delete(currentGrid);
}

void Canvas::draw() {
    /*Deltas represent the dimension of a box in the grid*/
    int deltaWidth = windowWidth/currentGrid->getWidth();
    int deltaHeight = windowHeight/currentGrid->getHeight();

    /*Renderer of the window*/
    SDL_Renderer *renderer = Window::getInstance()->getRenderer();

    /*Horizontal lines*/
    for (int h = 0; h <= windowHeight; h += deltaHeight) {
        SDL_RenderDrawLine(renderer, 0, h, windowWidth, h);
    }

    /*Vertical lines*/
    for (int w = 0; w <= windowWidth; w += deltaWidth) {
        SDL_RenderDrawLine(renderer, w, 0, w, windowHeight);
    }

    /*Draw the cells*/
    currentGrid->draw(windowHeight,windowWidth);
}

void Canvas::setGrid(Grid *other) {
    delete(currentGrid);
    currentGrid = other;
}

void Canvas::update() {
    /*Every cell of the canvas is checked*/
    for (int h = 0; h < currentGrid->getHeight(); ++h) {
        for (int w = 0; w < currentGrid->getWidth(); ++w) {
            int aliveNeighbours = 0;
            /*The neighbours of the dead cell are checked*/
            for (int i = -1; i < 2; ++i) {
                for (int j = -1; j < 2; ++j) {
                    if (i == 0 && j == 0) {
                        continue;
                    }
                    if (currentGrid->getValues(mod(h + i, currentGrid->getHeight()), mod(w + j, currentGrid->getWidth())) == 1) {
                        aliveNeighbours++;
                    }
                }
            }
            nextGrid->setValue(h,w,0);

            /*Creation of a new cell*/
            if (currentGrid->getValues(h,w) == 0 && (aliveNeighbours == 3 || aliveNeighbours == 6))
                nextGrid->setValue(h,w,1);

            /*Creation of a new cell*/
            else if (currentGrid->getValues(h,w) == 1 && (aliveNeighbours == 2 || aliveNeighbours == 3))
                nextGrid->setValue(h,w,1);

        }
    }

    /*The grid that is draw is updated*/
    delete(currentGrid);
    currentGrid = nextGrid;
    /*A new grid is created for the next iteration*/
    nextGrid = new Grid(currentGrid->getHeight(),currentGrid->getWidth());
}


