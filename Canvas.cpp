//
// Created by belisariops on 10/24/17.
//
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




