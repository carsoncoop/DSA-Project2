#include "Graph.h"
#include <chrono>


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

bool Maze::BFS(Position startPo, Position endPo, int up, int down, int left, int right) {
    return false;
}

bool Maze::DFS(Position startPo, Position endPo, int up, int down, int left, int right) {
    if (startPo.col == endPo.col && startPo.row == endPo.row) {
        std::cout << std::endl << "Depth-First Search Direction Results: " << std::endl;
        std::cout << "Up Count: " << up << std::endl;
        std::cout << "Down Count: " << down << std::endl;
        std::cout << "Left Count: " << left << std::endl;
        std::cout << "Right Count: " << right << std::endl;
        std::cout << "Total Count: " << up + down + left + right << std::endl;
        return true;
    }


    grid[startPo.row][startPo.col].visited = true;


    if (grid[startPo.row][startPo.col].up) {
        if (!grid[startPo.row - 1][startPo.col].visited) {
            startPo.row -= 1;
            up++;
            bool stop = DFS(startPo, endPo, up, down, left, right);
            startPo.row += 1;
            if (stop) {
                return true;
            }
        }
    }


    if (grid[startPo.row][startPo.col].down) {
        if (!grid[startPo.row + 1][startPo.col].visited) {
            startPo.row += 1;
            down++;
            bool stop = DFS(startPo, endPo, up, down, left, right);
            startPo.row -= 1;
            if (stop) {
                return true;
            }
        }


    }


    if (grid[startPo.row][startPo.col].left) {
        if (!grid[startPo.row][startPo.col - 1].visited) {
            startPo.col -= 1;
            left++;
            bool stop = DFS(startPo, endPo, up, down, left, right);
            startPo.col += 1;
            if (stop) {
                return true;
            }
        }


    }


    if (grid[startPo.row][startPo.col].right) {
        if (!grid[startPo.row][startPo.col + 1].visited) {
            startPo.col += 1;
            right++;
            bool stop = DFS(startPo, endPo, up, down, left, right);
            startPo.col -= 1;
            if (stop) {
                return true;
            }
        }

    }
    return false;
}



void Maze::runAlgorithms() {
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            grid[r][c].visited = false;
        }
    }

    std::chrono::steady_clock::time_point start1 = std::chrono::steady_clock::now();
    DFS(startPos, endPos);
    std::chrono::steady_clock::time_point end1 = std::chrono::steady_clock::now();

    std::chrono::duration<double> DFS_time = std::chrono::duration_cast<std::chrono::duration<double>>(end1 - start1);
    std::cout << "DFS took " << 1000 * 1000 * DFS_time.count() << " microseconds!" << std::endl;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            grid[r][c].visited = false;
        }
    }

    std::chrono::steady_clock::time_point start2 = std::chrono::steady_clock::now();
    BFS(startPos, endPos);
    std::chrono::steady_clock::time_point end2 = std::chrono::steady_clock::now();

    std::chrono::duration<double> BFS_time = std::chrono::duration_cast<std::chrono::duration<double>>(end2 - start2);
    std::cout << "BFS took " << 1000 * 1000 * BFS_time.count() << " microseconds!" << std::endl;
}
