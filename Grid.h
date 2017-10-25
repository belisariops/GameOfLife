//
// Created by belisariops on 10/24/17.
//

#ifndef GAMEOFLIFE_GRID_H
#define GAMEOFLIFE_GRID_H

/*Grid is going to be a one dimensional array
 * but it's going to receive call as a two
 * dimensional matrix, if the grid has a 1 on
 * position [i,j] then that position is painted*/
class Grid {
public:
    Grid(int height, int width);
    ~Grid();
    int getWidth()const;
    int getHeight()const;
    void setValue(int heightPosition,int widthPosition,int value);
    double getValues(int heightPosition,int widthPosition);

    void draw(int screenHeight, int screenWidth);

private:
    int height,width;
    int* values;

};


#endif //GAMEOFLIFE_GRID_H
