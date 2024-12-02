#ifndef GRID_H
#define GRID_H
#include <iostream>
struct Cell {
    Cell() : robot(nullptr) {};
    Cell(class Robot* robot) : robot(robot) {};
    class Robot* robot;
};

class Grid {
public:
    Grid(size_t height, size_t width);
    ~Grid();
    Cell* getCell(size_t x, size_t y);
    size_t getHeight();
    size_t getWidth();

private:
    Cell** grid;
    const size_t height;
    const size_t width;
};

#endif
