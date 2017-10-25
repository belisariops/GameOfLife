//
// Created by belisariops on 10/24/17.
//

#include <iostream>
#include "Canvas.h"
#include "Window.h"

Canvas::Canvas(int height, int width, int screenHeight, int screenWidth) {
    grid = new Grid(height, width);
    windowHeight = screenHeight;
    windowWidth = screenWidth;
}

Canvas::~Canvas() {
    delete(grid);
}

void Canvas::draw() {
    int deltaWidth = windowWidth/grid->getWidth();
    int deltaHeight = windowHeight/grid->getHeight();

    SDL_Renderer *renderer = Window::getInstance()->getRenderer();

    for (int h = 0; h <= windowHeight; h += deltaHeight) {
        SDL_RenderDrawLine(renderer, 0, h, windowWidth, h);
    }


    for (int w = 0; w <= windowWidth; w += deltaWidth) {
        SDL_RenderDrawLine(renderer, w, 0, w, windowHeight);
    }

    grid->draw(windowHeight,windowWidth);
}
