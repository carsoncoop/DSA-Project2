//Ensure walls are not destroyed on edges of maze
//Create start and end nodes at only at the edge of maze randomly
#include "Graph.h"



void Maze::generate() {
    //Generate random start point
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution rowRange(0, rows - 1);
    const int randRow = rowRange(gen);
    std::uniform_int_distribution colRange(0, cols - 1);
    const int randCol = colRange(gen);

    std::stack<Position> visitedStack;
    grid[randRow][randCol].visited = true; //Start point

    visitedStack.push(Position{randRow, randCol});


    while (!visitedStack.empty()) {
        Position currentPos = visitedStack.top();
        std::vector<Position> unvisitedNeighbors;

        //If neighbor(s) exist, populate vector of possible neighbor(s) to visit next:
        if (currentPos.row + 1 < rows) {//If lower neighbor exists
            if (!grid[currentPos.row + 1][currentPos.col].visited) {//If lower not visited
                unvisitedNeighbors.push_back({currentPos.row + 1, currentPos.col});
            }
        }
        if (currentPos.row - 1 >= 0) {//If upper neighbor exists
            if (!grid[currentPos.row - 1][currentPos.col].visited) {//If upper not visited
                unvisitedNeighbors.push_back({currentPos.row - 1, currentPos.col});
            }
        }
        if (currentPos.col + 1 < cols) {//If right neighbor exists
            if (!grid[currentPos.row][currentPos.col + 1].visited) {//If right not visited
                unvisitedNeighbors.push_back({currentPos.row, currentPos.col + 1});
            }
        }
        if (currentPos.col - 1 >= 0) {//If left neighbor exists
            if (!grid[currentPos.row][currentPos.col - 1].visited) {//If left not visited
                unvisitedNeighbors.push_back({currentPos.row, currentPos.col - 1});
            }
        }

        //Pick random neighbor from available options (if there are any)
        if (!unvisitedNeighbors.empty()) {
            std::uniform_int_distribution choiceRange(0, static_cast<int>(unvisitedNeighbors.size() - 1));
            Position pickedNeighborPos = unvisitedNeighbors[choiceRange(gen)];
            grid[pickedNeighborPos.row][pickedNeighborPos.col].visited = true;

            //Find wall to remove between current node & neighbor node
            if (pickedNeighborPos.row < currentPos.row) {//If upper neighbor was picked
                grid[pickedNeighborPos.row][pickedNeighborPos.col].down = true;
                grid[currentPos.row][currentPos.col].up = true;
            }
            else if (pickedNeighborPos.row > currentPos.row) {//If lower neighbor was picked
                grid[pickedNeighborPos.row][pickedNeighborPos.col].up = true;
                grid[currentPos.row][currentPos.col].down = true;
            }
            else if (pickedNeighborPos.col > currentPos.col){//If right neighbor was picked
                grid[pickedNeighborPos.row][pickedNeighborPos.col].left = true;
                grid[currentPos.row][currentPos.col].right = true;
            }
            else if (pickedNeighborPos.col < currentPos.col) {//If left neighbor was picked
                grid[pickedNeighborPos.row][pickedNeighborPos.col].right = true;
                grid[currentPos.row][currentPos.col].left = true;
            }
            visitedStack.push({pickedNeighborPos.row, pickedNeighborPos.col});
        }
        else {
            visitedStack.pop();
        }
    }


};

void Maze::print() const {
    // Top border
    for (int c = 0; c < cols; ++c) std::cout << "+--";
    std::cout << "+\n";

    for (int r = 0; r < rows; ++r) {
        std::cout << "|";
        for (int c = 0; c < cols; ++c) {
            std::cout << "  "; // cell interior (could mark start/end here)
            std::cout << (grid[r][c].right ? " " : "|");
        }
        std::cout << "\n";
        std::cout << "+";
        for (int c = 0; c < cols; ++c) {
            std::cout << (grid[r][c].down ? "  " : "--");
            std::cout << "+";
        }
        std::cout << "\n";
    }
}
