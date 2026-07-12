#include "priority_queue.hpp"
#include <stdexcept>

// -------------------------
//  Private helpers
// -------------------------

namespace {
    void swapPairs(std::pair<int,int>& a, std::pair<int,int>& b) {
        std::pair<int,int> temp = a;
        a = b;
        b = temp;
    }
}

// -------------------------
//  Constructors
// -------------------------

PriorityQueue::PriorityQueue(
        bool (*cmp)(const std::pair<int,int>&,
                    const std::pair<int,int>&))
        : heap{}, compare(cmp)
{ }

// -----------------------------------------------------------------------------
// Bulk-build constructor (1-based heap version)
//
// Converts an existing vector of (priority, payload) pairs into a valid
// 1-based binary min-heap using Floyd's heapify algorithm.
// -----------------------------------------------------------------------------
PriorityQueue::PriorityQueue(
        const std::vector<std::pair<int,int>>& data,
        bool (*cmp)(const std::pair<int,int>&,
                    const std::pair<int,int>&))
        : compare(cmp)
{
    // Allocate heap with one extra slot so heap indexing starts at index 1.
    heap.resize(data.size() + 1);

    // Copy incoming data into positions 1..n (heap[0] remains unused).
    for (std::size_t i = 0; i < data.size(); ++i) {
        heap[i + 1] = data[i];
    }

    // If no elements, nothing to do.
    if (data.empty()) return;

    int n = static_cast<int>(data.size());

    // -------------------------------------------------------------------------
    // Floyd's bottom-up heap construction.
    //
    // We start at the last internal node, which is n/2.
    // Every node > n/2 is a leaf and already satisfies heap property.
    //
    // Loop backwards to index 1, bubble-down each node.
    // -------------------------------------------------------------------------
    for (int i = n / 2; i >= 1; --i) {

        int parent = i;

        // Bubble-down to restore heap property.
        while (true) {

            int left  = 2 * parent;       // left child index
            int right = 2 * parent + 1;   // right child index

            int smallest = parent;        // assume parent is smallest

            // If left child exists and has higher priority (smaller key)
            if (left <= n &&
                compare(heap[left], heap[smallest])) {
                smallest = left;
            }

            // If right child exists and has even smaller key
            if (right <= n &&
                compare(heap[right], heap[smallest])) {
                smallest = right;
            }

            // If parent is already smallest, heap property is satisfied
            if (smallest == parent)
                break;

            // Otherwise swap parent with the smallest child
            swapPairs(heap[parent], heap[smallest]);

            // Continue bubbling from the child position
            parent = smallest;
        }
    }
}



// -------------------------
//  Core Operations
// -------------------------

void PriorityQueue::insert(const std::pair<int,int>& v) {
    heap.push_back(v);

    // Bubble-up
    int child = static_cast<int>(heap.size()) - 1;
    while (child > 0) {
        int parent = (child - 1) / 2;
        if (!compare(heap[child], heap[parent]))
            break;  // heap order satisfied

        swapPairs(heap[child], heap[parent]);
        child = parent;
    }
}

const std::pair<int,int>& PriorityQueue::findMin() const {
    if (empty())
        throw std::runtime_error("findMin on empty PriorityQueue");

    return heap[0];
}

void PriorityQueue::deleteMin() {
    if (empty())
        throw std::runtime_error("deleteMin on empty PriorityQueue");

    // Move last element to root and pop
    heap[0] = heap.back();
    heap.pop_back();

    // Bubble-down
    int parent = 0;
    while (true) {
        int left     = 2 * parent + 1;
        int right    = 2 * parent + 2;
        int smallest = parent;

        if (left < static_cast<int>(heap.size()) &&
            compare(heap[left], heap[smallest])) {
            smallest = left;
        }
        if (right < static_cast<int>(heap.size()) &&
            compare(heap[right], heap[smallest])) {
            smallest = right;
        }
        if (smallest == parent)
            break;

        swapPairs(heap[parent], heap[smallest]);
        parent = smallest;
    }
}

std::pair<int,int> PriorityQueue::extractMin() {
    std::pair<int,int> min = findMin();  // will throw if empty
    deleteMin();
    return min;
}

// -------------------------
//  Inspectors / Modifiers
// -------------------------

bool PriorityQueue::empty() const noexcept {
    return heap.empty();
}

std::size_t PriorityQueue::size() const noexcept {
    return heap.size();
}

void PriorityQueue::clear() noexcept {
    heap.clear();
}

void PriorityQueue::reserve(std::size_t n) {
    heap.reserve(n);
}
