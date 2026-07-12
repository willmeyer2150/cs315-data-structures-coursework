#include "heap.hpp"
#include <iostream>
#include <stdexcept>
#include <utility>   // for std::swap

void printHeap(const std::vector<int>& heap) {
    std::cout << "Heap (1 based): ";
    for (std::size_t i = 1; i < heap.size(); ++i) {
        std::cout << heap[i] << " ";
    }
    std::cout << std::endl;
}

void heapInsert(std::vector<int>& heap, int x) {
    heap.push_back(x);
    std::size_t i = heap.size() - 1;

    // Bubble up
    while (i > 1) {
        if (heap[i] < heap[i/2]) {
            std::swap(heap[i], heap[i/2]);
            i /= 2;
        }
        else {
            break;
        }
    }
}

void heapDeleteMin(std::vector<int>& heap) {
    if (heap.size() <= 1) {
        throw std::runtime_error("Heap is empty");
    }

    if (heap.size() == 2) {
        heap.pop_back();
        return;
    }

    heap[1] = heap.back();
    heap.pop_back();

    // bubble down

    std::size_t i = 1;
    std::size_t n = heap.size() - 1;

    while (i <= n / 2) {
        std::size_t leftChild = 2 * i;
        std::size_t rightChild = leftChild + 1;
        if (leftChild < n && heap[leftChild] > heap[rightChild]) {
            ++leftChild;
        }
        if (heap[i] <= heap[leftChild]) {
            break;
        }
        std::swap(heap[i], heap[leftChild]);
        i = leftChild;

    }


}