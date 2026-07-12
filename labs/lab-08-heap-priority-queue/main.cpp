#include <iostream>
#include <fstream>
#include <ranges>

#include "PriorityQueue.hpp"

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.

int main(int argc, char *argv[]) {

    if (argc != 2) {
        std::cout << "usage: " << argv[0] << " nameOfAnInputFile\n";
        exit(1);
    }
    std::fstream inputStream;
    inputStream.open(argv[1], std::ios::in);
    if (!inputStream.is_open()) {
        std::cout << "Unable to open " << argv[1] << ". Terminating...";
        exit(1);
    }

    PriorityQueue heapOrderedTree;
    int value, numValues = 0;
    while (inputStream >> value) {  // n * log n \in O(n log n)
        heapOrderedTree.insert(value); // O(log n)
        numValues++;
    }

    std::cout << "Inserted " << numValues << " values in the heap.\n";
    std::cout << "The heap has " << heapOrderedTree.size() << " elements.\n";

    int numValuesDeleted = 0;
    while (!heapOrderedTree.empty()) { // n * log n \in O(n log n)
        std::cout << heapOrderedTree.findMin() << std::endl; // O(1)
        heapOrderedTree.deleteMin(); // O(log n)
        numValuesDeleted++;
    }
    std::cout << "Deleted " << numValuesDeleted << " values from the heap.\n";

    std::cout << "The heap has " << heapOrderedTree.size() << " elements.\n";
    return 0;
}
