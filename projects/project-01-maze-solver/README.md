# Project 1 — Stack-Based Maze Solver

**Author:** Will Meyer

This C++ program reads a maze from a text file and searches for a route between
its two boundary openings. It uses an explicit stack and iterative backtracking
to explore the maze. When it finds a route, it prints the maze with the solution
path marked by red asterisks.

See [ASSIGNMENT.md](ASSIGNMENT.md) for a condensed summary of the original
instructor-provided project brief.

## Build and Run

The project requires C++20. From this directory, build it with CMake:

```bash
cmake -S . -B build
cmake --build build
./build/CS315_Will_Meyer_Solving_A_Maze_Project maze0-1_input.txt
```

It can also be compiled directly, matching the original course testing
environment:

```bash
mkdir -p build
g++ -std=c++20 main.cpp Maze.cpp -o build/maze-solver
./build/maze-solver maze0-1_input.txt
```

The input must be a rectangular grid containing only `0`s and `1`s, with no
spaces between cells. A `0` is an open cell and a `1` is a wall. The maze must
have exactly two openings along its outer boundary.

## Implementation Details

I followed the project brief by first reading the input grid from a text file
and printing it back to the terminal. Once that worked, I implemented `Maze.h`
and `Maze.cpp`.

The `Maze` class stores:

- The maze as a two-dimensional vector.
- A stack that tracks the current path.
- Row-and-column tuples for the start and goal openings.

Its operations include finding the boundary openings, checking grid bounds,
finding and pushing unexplored neighbors, searching for a path, and printing
the solution. Neighbors are considered in the order down, right, up, and left.
The grid is updated during the search so the program can distinguish unexplored
cells, the active route, and cells that have already been examined.

Initially, I had almost all the pathfinding logic hardcoded into a single
`findPath()` function. After seeking advice, it became clear that this approach
was too complicated and did not work anyway. After much thought, trial, and
error, I learned how to delegate specific tasks to helper functions. This made
the maze-solving process much more modular and easier to understand.

In the past, I struggled with helper functions because tracking where variables
were passed seemed complicated. This project helped me level up and made me
more comfortable breaking a larger problem into smaller operations.

## Testing and Status

I originally built and tested the program in CLion. It solves the provided
`maze0-1_input.txt` fixture and can work with other rectangular mazes whose two
openings occur anywhere on the boundary. The final output shows the solution
route with red asterisks. I also tested an unsolvable maze, for which the program
reports that no path was found.

I compiled and tested the project on the course's Blue server to confirm that
it worked in the required environment. In the final implementation, I added
support for `argv` so the program can read a maze from a file path supplied on
the command line. Argument handling was new to me, and I used ChatGPT for
guidance while setting it up.

## Collaboration and Sources

This project is the product of my own work. All code and logic are mine except
where described below.

- **Regina, during office hours:** We discussed the use of `std::tuple` and
  `std::stack`, the start/goal search, the logic of `findPath()`, and how to
  visualize a vector of vectors.
- **Dr. Kooshesh, during office hours:** He helped clarify the logic of
  `findPath()` and suggested simplifying it with helper functions. We discussed
  marking cells in the input grid with additional values to track whether they
  had been explored.
- **GeeksforGeeks:** I consulted its article on
  [tuples in C++](https://www.geeksforgeeks.org/cpp/tuples-in-c/) to better
  understand tuple usage.
- **ChatGPT:** I used ChatGPT to brainstorm grid-search behavior; review syntax
  I had forgotten, such as file input, ASCII-to-integer conversion, and stack
  printing; learn how to pass an input path through `argv`; and get advice on
  repository and README organization. I reviewed and adapted suggestions to fit
  my own code and logic.
