//
// Created by Will Meyer on 9/5/25.
//
// Maze.cpp
// Implementaion of a backtracking solver for a grid maze of 0's and 1's
// Grid formation at solution: 0 = path, 1 = wall, 2 = current solution and explored path, 3 = confirmed explored wall
// Neighbor cells are searched in order: Down, Right, Up, Left
// Cells that remain a 2 at the end are on the stack which represents the path from start to goal, but in reverse order
// If a path is found, the grid is printed with red asterisks for path, else the program reports no path is found.
#include "Maze.h"

#include <iostream>
#include <ostream>

// Maze constructor
// Pre-condition: Takes an input grid passed from main
// Post condition: grid is initialized from the inputGrid
Maze::Maze(const std::vector<std::vector<int>>& inputGrid)
{
    grid = inputGrid;
}


// Accessor for number of rows
// Pre-condition: Reads in the grid
// Post-codntion: Returns grid.size.
size_t Maze::rows() const
{
    return grid.size();
}


// Accessor for number of columns
// Pre-condition: Reads in the grid
// Post-codntion: Returns grid.size[0]
size_t Maze::cols() const
{
    return grid[0].size();
}


// findPath
// Pre-condition: The Grid is loaded and findStartGoal() locates the start and goal positions.
// Post-condition: If a path is found, the cells along the path are now set to 2 and the stack contains the route. If no path is found, the stack is empty.
// The top of the stack always contains the most current locaiton on the path. If that cell is deemed not on the path, it is turned into a 3 to indicate
// not on the path and already explored.
void Maze::findPath() {
    findStartGoal();
    int r = std::get<0>(start);
    int c = std::get<1>(start);

    //Push the start cell onto the stack
    s.push(start);
    grid[r][c] = 2;

    //  While the stack is not empty do
    while (!s.empty()) {
        int r = std::get<0>(s.top());
        int c = std::get<1>(s.top());

        if (s.top() == goal)
        {
            std::cout << "Path Found!" << std::endl;
            std::cout << std::endl;
            printSolution();
            break;
        }

        if (findUnexploredNeighbor(r, c)) // if neighbor is unexplored, keep going
        {
            continue;
        }
        else    // else, convert the location on the grid to a 3 and pop() the stack to move back 1
        {
            grid[r][c] = 3;
            s.pop();
        }
    }

    if (s.empty())
    {
        std::cout << "No path found." << std::endl;
        printSolution();
    }
}


// findStartGoal
// Pre-condition: The grid is loaded
// Post-condition: If exactly 2 openings are found, start = 1st opening, goal = second opening.
// If no openings are found, the program will print an error message and state the maze is not solvable.
void Maze::findStartGoal()
{
    std::vector<std::tuple<int, int>> openings;

    size_t lastRow = rows() - 1;
    size_t lastCol = cols() - 1;

    // scan top row (0, c)
    for (size_t c = 0; c <= lastCol; ++c)
        {
            if (grid[0][c] == 0)
            {
                openings.push_back(std::make_tuple(0, c));
            }
        }

    // Scan bottom row (lastRow, c)
    for (size_t c = 0; c <= lastCol; ++c)
    {
        if (grid[lastRow][c] == 0)
        {
            openings.push_back(std::make_tuple(lastRow, c));
        }
    }

    // Scan left collumn (r, 0)
    for (size_t r = 0; r <= lastRow; ++r)
    {
        if (grid[r][0] == 0)
        {
            openings.push_back(std::make_tuple(r, 0));
        }
    }

    // Scan right collumn (r, lastCol)
    for (size_t r = 0; r <= lastRow; ++r)
    {
        if (grid[r][lastCol] == 0)
        {
            openings.push_back(std::make_tuple(r, lastCol   ));
        }
    }

    if (openings.size() == 2)
    {
        start = openings.front();
        goal = openings.back();
        std::cout << "Openings found: " << openings.size() << std::endl;
        for (const auto &t : openings)
        {
            std::cout << "(" << std::get<0>(t) << ", " << std::get<1>(t) << ")" << std::endl;
        }
    }
    else
    {
        std::cerr <<"Expected 2 openings, but found: " << openings.size() << ", this maze is not solvable." << std::endl;
    }
}


// findUnexploredNeighbor
// Pre-conditions: Reads in the current location (r,c) and explores neighbors in order of Down, Right, Up, Left.
// Returns true after pushing the first open neighbor, a 0, with helper function: pushNeighbor(), else returns false.

bool Maze::findUnexploredNeighbor(int r, int c)
{
    if (pushNeighbor(r+1, c)) // check down
    {
        return true;
    }
    if (pushNeighbor(r, c+1)) // check right
    {
        return true;
    }
    if (pushNeighbor(r-1, c)) // check up
    {
        return true;
    }
    if (pushNeighbor(r, c-1)) // check left
    {
        return true;
    }
    else return false;
}


// pushNeighbor
// Pre-condition: Reads in the current neighbor to check as (r,c).
// Post-condition: checkBounds() confirms we are in the boundary of the grid
// Post-condition: If (r,c) = 0, it pushes (r,c) on the stack and marks it as a 2 - returns true
// If (r,c) = 1, it is a wall and so mark it as a 3, return false.
// else, if it is 2 or 3, return false.
bool Maze::pushNeighbor(int r, int c)
{
    if (!checkBounds(r, c)) // make sure you do not check out of bounds of the grid
    {
        return false;
    }

    if (grid[r][c] == 0) // it's a path, so push on the stack
    {
        s.push(std::make_tuple(r, c));
        grid[r][c] = 2; // mark as 2 to keep track of where we have been
        return true;
    }
    else if (grid[r][c] == 1) // no path, it's a wall
    {
        grid[r][c] = 3; // mark as a 3 to keep track of where we have been
        return false;
    }
    else
    {
        return false; // if you encounter a 2 or a 3 again, move on.
    }
}


// checkBounds
// Returns true if (r,c) is in bounds. Helper function for pushNeighbor.
bool Maze::checkBounds(int r, int c)
{
    return (r >= 0 && static_cast<size_t>(r) < rows() && c >= 0 && static_cast<size_t>(c) < cols());
}


// printSolution
// Prints the current grid. Path cells that were a 2 are converted to a red asterisk and will print the pathway within the grid
void Maze::printSolution() const
{
    for (size_t i = 0; i < grid.size(); ++i)
        {
        for (size_t j = 0; j < grid[i].size(); ++j)
            {
            int v = grid[i][j];
            if (v == 2)
            {
                std::cout << "\033[31m*\033[0m"; // change the path marker to * in red
            }
            else
            {
                std::cout << v; // 0, 1 or 3 stay the same
            }
        }
        std::cout << '\n';
    }
}