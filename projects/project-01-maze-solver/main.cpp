//
// Created by Will Meyer on 9/5/25.
//
// Solving a Maze Project
// main.cpp
// Reads in and outputs a maze grid in the form of a text file of 0's and 1's
// Searches the grid for openings that signify start and goal points
// Solves the maze from the start point by searching neighbor cells in a D,U,R,L pattern for open pathways
// If a path is found to the goal, the program outputs the grid with a red asterisk in place of all points along the path
// If no path is found, the program correctly outputs the maze is not solvable.


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Maze.h"

int main(int argc, char* argv[])
{
    // Require a file path argument
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input-file>" << std::endl;
        return 1;
    }

    // Open argv[1] instead of a hardcoded filename
    std::ifstream in(argv[1]);
    if (!in)
    {
        std::cerr << "Error: couldn't open '" << argv[1] << "'" << std::endl;
        return 1;
    }

    std::string line;
    std::vector<std::vector<int>> grid;

    while (std::getline(in, line))
    {
        std::vector<int> row;
        for (size_t i = 0; i < line.size(); ++i)
        {
            int value = line[i] - '0';   // assumes only 0 or 1 as input
            row.push_back(value);
        }
        grid.push_back(row);
    }

    for (size_t i = 0; i < grid.size(); ++i)
    {
        for (size_t j = 0; j < grid[i].size(); ++j)
        {
            std::cout << grid[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    int r = grid.size();
    int c = grid[0].size();
    std::cout << "There are " << r << " rows in this grid." << std::endl;
    std::cout << "There are " << c << " columns in this grid." << std::endl;
    std::cout << std::endl;

    Maze maze(grid);
    maze.findPath();

    return 0;
}

