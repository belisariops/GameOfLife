//
// Created by belisariops on 10/24/17.
//

#include <SDL2/SDL_render.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
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

Grid::Grid(const Grid &other) {
    int elements = other.width*other.height;
    height = other.height;
    width = other.width;
    values = new int[elements];
    for (int i = 0; i < elements; ++i) {
        values[i] = other.values[i];
    }

}

Grid &Grid::operator=(const Grid &other) {
    if (&other != this) {
        height = other.getHeight();
        width = other.getWidth();
        values = new int[height * width];
        for (int i = 0; i < height * width; i++) {
            values[i] = other.values[i];
        }

    }

    return *this;
}

void Grid::loadFromFile(std::string path) {
    std::ifstream infile(path.c_str());
    std::string line;
    std::vector<std::vector<int>> block;
    while (std::getline(infile, line))
    {
        std::istringstream iss(line);
        int n;
        std::vector<int> l;

        while (iss >> n)
        {
            l.push_back(n);
        }

        block.push_back(l);
    }

    int iinitialHeightPosition = (width - block.size())/2;
    int initialWidthPosition = (height - block[0].size())/2;
    for (int i = 0; i < block.size(); ++i) {
        for (int j = 0; j < block[i].size(); ++j) {
            setValue(i + initialWidthPosition,j + iinitialHeightPosition,block[j][i]);
        }
    }
}





