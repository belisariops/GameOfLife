//
// Created by belisariops on 10/24/17.
//

#include "Grid.h"

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




