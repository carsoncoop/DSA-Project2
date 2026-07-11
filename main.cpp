#include<iostream>
#include "Graph.h"

int main() {

    Maze maze(317,317);
    // 317*317 = 100489 nodes
    maze.generate();
    std::cout << "maze generated" << std::endl;
    //maze.print(); // takes too long to print for large mazes, breaks past cols=39
    maze.runAlgorithms();
    return 0;
}