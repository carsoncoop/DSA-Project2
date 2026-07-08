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
    //Assign startPos & endPos
    std::bernoulli_distribution vertOrHorizStart(0.5);
    const bool vertStart = vertOrHorizStart(gen);

    if (vertStart) {

        std::bernoulli_distribution leftOrRightStart(0.5);
        const bool leftStart = leftOrRightStart(gen);

        if (leftStart) {
            startPos.col = 0;
            endPos.col = cols - 1;
        }
        else {
            startPos.col = cols - 1;
            endPos.col = 0;
        }

        std::uniform_int_distribution rowStartRange(0, rows - 1);
        startPos.row = rowStartRange(gen);
        std::uniform_int_distribution rowEndRange(0, rows - 1);
        endPos.row = rowEndRange(gen);
    }
    else {

        std::bernoulli_distribution topOrBottomStart(0.5);
        const bool topStart = topOrBottomStart(gen);

        if (topStart) {
            startPos.row = 0;
            endPos.row = rows - 1;
        }
        else {
            startPos.row = rows - 1;
            endPos.row = 0;
        }

        std::uniform_int_distribution colStartRange(0, cols - 1);
        startPos.col = colStartRange(gen);
        std::uniform_int_distribution rowEndRange(0, cols - 1);
        endPos.col = rowEndRange(gen);
    }
    //Start point is 100% random, and end point will always be on the opposite edge, but besides that, is random too
};

void Maze::print() const {
    for (int c = 0; c < cols; ++c) std::cout << "+--";
    std::cout << "+\n";


    for (int r = 0; r < rows; ++r) {
        std::cout << "|";
        for (int c = 0; c < cols; ++c) {
            std::cout << "  ";
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

    std::cout << std::endl;
    std::cout << "Start --> Row: " << startPos.row << ", Col: " << startPos.col << std::endl;
    std::cout << "End --> Row: " << endPos.row << ", Col: " << endPos.col << std::endl;
    std::cout << "(Indexing for Row & Col starts at 0)" << std::endl;
}
