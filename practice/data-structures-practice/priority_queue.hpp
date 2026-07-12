#pragma once

#include <utility>   // std::pair
#include <cstddef>   // std::size_t
#include <vector>    // std::vector

// A simple min-priority queue interface.
// The priority is stored in the first element of the pair.
// The second element can be any payload (e.g., an ID).

class PriorityQueue {
public:
    // 1. Empty PQ with a priority comparator.
    PriorityQueue(bool (*cmp)(const std::pair<int,int>&,
                              const std::pair<int,int>&));

    // 2. Bulk-build from existing data.
    PriorityQueue(const std::vector<std::pair<int,int>>& data,
                  bool (*cmp)(const std::pair<int,int>&,
                              const std::pair<int,int>&));

    // Rule of 0 is fine (vector handles its own memory).
    ~PriorityQueue() = default;

    // Core operations.
    void insert(const std::pair<int,int>& v);   // insert item
    const std::pair<int,int>& findMin() const;  // return smallest key
    void deleteMin();                           // remove smallest key
    std::pair<int,int> extractMin();            // return + remove

    // Inspectors.
    [[nodiscard]] bool empty() const noexcept;
    [[nodiscard]] std::size_t size() const noexcept;

    // Modifiers.
    void clear() noexcept;
    void reserve(std::size_t n);

private:
    // Underlying structure: a binary heap stored in a vector.
    // Heap property is defined by 'compare'.
    std::vector<std::pair<int,int>> heap;
    bool (*compare)(const std::pair<int,int>&,
                    const std::pair<int,int>&);
};
