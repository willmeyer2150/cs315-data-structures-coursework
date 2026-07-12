//
// Created by Will Meyer on 9/5/25.
// Maze.h
// Defines a maze class with a stack based pathway finder with 0 = to a path, 1 = to a wall, 2 = to a path that has been explored
// and 3 = to a wall that has been explored

#ifndef CS315_WILL_MEYER_SOLVING_A_MAZE_PROJECT_MAZE_H
#define CS315_WILL_MEYER_SOLVING_A_MAZE_PROJECT_MAZE_H

#include <vector>
#include <stack>
#include <tuple>

class Maze {
public:
    Maze(const std::vector<std::vector<int>> &grid); // Constructor from an input grid. Rectangular grid of 0's and 1's.
    size_t rows() const; // number of rows
    size_t cols() const; // number of columns
    void findPath();
    void findStartGoal();
    bool findUnexploredNeighbor(int r, int c);
    bool pushNeighbor(int r, int c);
    bool checkBounds(int r, int c);
    void printSolution() const;

// Data members
private:
    std::vector<std::vector<int>> grid; // input grid
    std::stack<std::tuple<int, int>> s; // stack for tracking the path
    std::tuple<int, int> start;
    std::tuple<int, int> goal;
};

#endif //CS315_WILL_MEYER_SOLVING_A_MAZE_PROJECT_MAZE_H
