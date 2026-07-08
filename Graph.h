#ifndef DSAPROJECT2_GRAPH_H
#define DSAPROJECT2_GRAPH_H
#include <vector>
#include <random>
#include <iostream>
#include <stack>


struct Position {
    int row, col;
};

class Maze {

    struct Cell {

        bool up, down, left, right, visited;

        Cell () : up(false), down(false), left(false), right(false),
            visited(false) {}
    };

    int rows;
    int cols;
    std::vector<std::vector<Cell>> grid;

public:

    Maze(const int rows, const int cols):
    rows(rows), cols(cols), grid(rows, std::vector<Cell>(cols)){} //Grid populated with default cells

    void generate();
    void print() const;//Useful for debugging

    Position startPos, endPos;
};


#endif //DSAPROJECT2_GRAPH_H
