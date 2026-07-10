#include<iostream>
#include "Graph.h"

int main() {

    Maze maze(20,20);
    maze.generate();
    maze.print();
    maze.runAlgorithms();
    return 0;
}