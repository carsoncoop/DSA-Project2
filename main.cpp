#include<iostream>
#include "Graph.h"

int main() {

    Maze smallMaze(20, 20);
    smallMaze.generate();
    smallMaze.print();
    smallMaze.runAlgorithms();

    std::cout << std::endl << std::endl << "### 100,000 Node Maze ###" << std::endl << std::endl;

    Maze maze(317, 317);
    // 317*317 = 100489 nodes
    maze.generate();
    std::cout << "Start position: " << maze.startPos.row << ", " << maze.startPos.col << std::endl;
    std::cout << "End position: " << maze.endPos.row << ", " << maze.endPos.col << std::endl;
    //maze.print(); // takes too long to print for large mazes, breaks past cols=39
    maze.runAlgorithms();
    return 0;
}