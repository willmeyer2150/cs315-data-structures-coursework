# Project 1 Assignment: Solving a Maze

> This is a condensed, paraphrased archive of the instructor-provided project
> brief, originally distributed as `CS 315_Project01_Solving_A_Maze.docx`.
> Administrative submission details and an unrelated personal Git cheat sheet
> from the source document have been omitted.

## Objective

Write a C++ application that solves a maze with an iterative, stack-based
backtracking algorithm. The exercise connects recursive problem solving with an
explicit stack and provides practice designing a class that encapsulates both
maze data and maze-solving behavior.

## Maze Model

- The maze is a rectangular grid of `0` and `1` values.
- A `0` represents an open path cell.
- A `1` represents a wall cell.
- A cell is identified by its row and column.
- Two path cells are adjacent when one is immediately above, below, left, or
  right of the other; diagonal movement is not allowed.
- The maze boundary consists of walls except for two open cells: the start and
  target.

Although the open cells and their adjacency relationships can be understood as
a graph, the program should traverse that graph implicitly through the grid
rather than constructing a separate graph data structure.

## Required Algorithm

Use a stack to track the current route and backtrack from dead ends:

```text
push the start cell

while the stack is not empty:
    if the top cell has no unexplored adjacent cell:
        pop the top cell
    else:
        choose an unexplored adjacent cell
        push it
        mark it explored

        if it is the target:
            stop searching

if the stack is empty:
    no solution exists
else:
    the stack contains the solution path in reverse order
```

The choice among multiple unexplored neighbors does not need to be optimal. If
a choice leads to a dead end, the program should backtrack until another choice
is available.

## Input Requirements

- Read the maze from a text file supplied as a command-line argument.
- Each line contains a row of consecutive `0` and `1` characters with no
  spaces.
- Convert the characters into a suitable two-dimensional representation, such
  as a vector of vectors.
- Locate the two boundary openings after reading the file.
- The assignment permits assuming that the input is valid and that all rows
  have the same width.

## Output Requirements

- Print the maze to standard output.
- If a solution exists, identify the cells on its path.
- The default specification replaces path cells with spaces, but a special
  character such as `*` is permitted.
- ANSI terminal colors may optionally be used; the brief specifically suggests
  a red asterisk (`"\033[31m*\033[0m"`).
- If the maze has no solution, print a message explaining that no path exists.

## Suggested Development Sequence

1. Read the input file and print it unchanged.
2. Convert each input row from characters into a two-dimensional grid.
3. Find and mark the start and target cells.
4. Implement neighbor exploration.
5. Add stack-based backtracking.
6. Keep maze operations modular inside a `Maze` class.

The suggested structures include a two-dimensional vector for the grid and a
stack for the active path.

## Evaluation Contract

The project was tested on the course's Blue system using commands equivalent to:

```bash
unzip NameOfProject.zip
cd NameOfProject
g++ -std=c++20 *.cpp
./a.out name-of-an-input-file
```

The program therefore needed to compile as C++20, accept the input filename on
the command line, and print its results to standard output.

## Original Submission Requirement

The original submission was a ZIP archive of the complete project directory,
including the course-required README, submitted through Canvas.

