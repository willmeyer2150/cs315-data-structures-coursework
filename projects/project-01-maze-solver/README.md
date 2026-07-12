## Student Information

Name: Will Meyer

## Collaboration & Sources
This project is the product of my own work. All code and the logic contained in it is mine except where stated below.
* Person consulted: Regina during office hours (Topics discussed: Proper implementation of std::tuple and std::stack, discussed code logic for start/goal search as well as for the findPath() function. She also clarified how a vector of vectors should be visualized.)
* Person consulted: Dr. Kosheesh during office hours (Topics discussed: clarified the logic of the findPath() function with the goal of simplifying my code. Recommended approach: Modifying the input grid using a helper function to turn 0's or 1's into 2's or 3's in order to track if a cell has been explored or not.)
* Website Resources: https://www.geeksforgeeks.org/cpp/tuples-in-c/ (Used to understand tuple implementation)
* AI Use: Chatgpt (Used for brainstorming search functionality within an input grid. I adapted answers using my own code and logic. I also prompted for information on how to maintain a private git repo for this project which I pushed to throughout. Additionally, I sought out best practice advice for ordering functiions in a header file and for crafting a proper README.md. All code  and logic implementation came from me except for small sections which I had forgotten such as reading an input file, converting ASCII characters to integers and stack printing. Any code suggestions were adapted using my own code.)

## Iplementation Details
I followed the project brief instructions and began by reading the inputgrid into the program from a text file. Once I had printed the grid to output, I implemented Maze.h and Maze.cpp.
* Private variables: the input grid, a stack, and start/goal tuples for the boundary openings. 
* Public functions: a constructor, two accessors for row/column counts, findPath(), and helper functions findStartGoal, findUnexploredNeighbor, pushNeighbor, checkBounds, and printSolution.
* Initially, I had almost all the path finding logic hardcoded into a single function called findPath(). After seeking out advice, it became clear that this approach was too complicated and did not work anyway. After much thought and trial and error, I discovered how to delegate specific tasks to helper functions which would perform the task of solving the maze in a much more modular package which is easy to understand and read. In the past, I have struggled with helper functions because tracking where variables were passed seemed complicated, but this project has helped me level up and now I feel more comforatable with that type of coding.
* Process of Writing Helper Functions: This project has helped me refine my ability to utilize helper functions. 

## Testing & Status
This program has been built and tested using CLion. It does solve a maze using the provided inputfile, maze()-1_input.txt, and it can also solve mazes of other formats when openings are found on the top and bottom. The final output is that of a solved maze with red asterisks in place of the open pathway. I also tested my program with an unsolvable maze and the program successfully outputs that no path can be found.
* Testing on Blue Server: I compiled and tested my program on blue to confirm functionality per the project instructions.
* Final implementation: I added support for argv[] so the program can read the maze from a file path passed on the command line. This was new to me, and I used ChatGPT for guidance on setting up the argument handling.
