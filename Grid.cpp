//
// Created by belisariops on 10/24/17.
//

#include <SDL2/SDL_render.h>
#include "Grid.h"
#include "Window.h"

Grid::Grid(int height, int width) : height(height),width(width)  {
    this->values = new int[height * width];
}

Grid::~Grid() {
    delete[] this->values;
}


int Grid::getHeight() const {
    return height;
}


int Grid::getWidth() const {
    return width;
}

void Grid::setValue(int heightPosition, int widthPosition, int value) {
    values[width*heightPosition + widthPosition] = value;
}

double Grid::getValues(int heightPosition, int widthPosition) {
    return values[width*heightPosition + widthPosition];
}

void Grid::draw(int screenHeight, int screenWidth) {
    int deltaHeight = screenHeight/height;
    int deltaWidth = screenWidth/width;
    SDL_Renderer *renderer = Window::getInstance()->getRenderer();
    SDL_Rect rectangle;
    for (int i = 0; i < (height * width); i++) {
        if (values[i] == 1) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 220);
            rectangle.x = (i % width) * deltaWidth;
            rectangle.y = (i / width) * deltaHeight;
            rectangle.w = deltaWidth;
            rectangle.h = deltaHeight;
            SDL_RenderFillRect(renderer, &rectangle);
        }
    }
}





