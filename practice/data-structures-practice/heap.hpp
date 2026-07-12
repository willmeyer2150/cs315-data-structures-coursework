#pragma once
#include <vector>

// A simple 1-based min-heap using a vector<int>.
// heap[0] is unused. Caller must ensure heap[0] exists.

void printHeap(const std::vector<int>& heap);

// Insert an element into the heap (bubble-up)
void heapInsert(std::vector<int>& heap, int x);

// Delete the minimum element (bubble-down)
// Throws std::runtime_error if empty.
void heapDeleteMin(std::vector<int>& heap);

