//
// Created by Kooshesh on 10/15/25.
//

// Team Names: Will Meyer, Caleb Clements

#include<cassert>
#include "PriorityQueue.hpp"

PriorityQueue::PriorityQueue() {
    heap.push_back(0); // guarantee vector of size 1, an empty vector for our purposes.
}

bool PriorityQueue::insert(int v) {
    heap.push_back(v); // populate the vector
    int i = heap.size() - 1;
    int parent = (i/2); // assign parent variable for better understanding

    // loop while values exist at index 1 and for as long as current i is less than its parent
    while (i > 1 && heap[i] < heap[parent]) {
        std::swap(heap[i], heap[i/2]);
        i = parent;
    }
    return true;
}


void PriorityQueue::deleteMin() {
    assert(!empty());
    std::swap(heap[1], heap[heap.size() - 1]); // Swap the root with the last item in the complete tree
    heap.pop_back(); // delete the former root, the min

    // if the size is now 1, nothing left in the tree.
    if (heap.size() == 1) {
        return;
    }

    int i = 1;
    // loop while a left child exists
    while (2 * i < heap.size()) {
        int left = 2 * i; // improve clarity
        int right = 2 * i + 1; // improve clarity
        int minChild = left; // initialize minChild to left child.

        // if a right child exists and right < left, change minChild to right child
        if (right < heap.size() && heap[right] < heap[left]) {
            minChild = right;
        }

        // If parent <= minChild, you're done, exit.
        if (heap[i] <= heap[minChild]) {
            break;
        }

        // Otherwise, swap i and minChild and move down
        std::swap(heap[i], heap[minChild]);
        i = minChild;
    }
}

int PriorityQueue::findMin() const {
    assert(!empty());
    return heap[1];
}

bool PriorityQueue::empty() const {
    if (heap.size() == 1) {
        return true;
    }
    return false;
}

unsigned long PriorityQueue::size() {
    return static_cast<unsigned long>(heap.size() - 1); // account for unused i = 0
}