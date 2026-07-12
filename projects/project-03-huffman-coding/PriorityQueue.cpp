//
// Created by Will H Meyer on 10/11/25.
//

#include "PriorityQueue.hpp"

#include <vector>
#include <iostream>
#include <cassert>
#include <utility>   // std::swap
#include <cstddef>   // std::size_t

#include "TreeNode.hpp"

// Non‑owning: does NOT delete the TreeNode* it stores.
// The constructor takes an initial set of leaves and sorts them internally.
PriorityQueue::PriorityQueue(std::vector<TreeNode*> nodes) {
    items_.reserve(nodes.size());   // avoid reallocating
    for (std::size_t i = 0; i < nodes.size(); ++i) {
        TreeNode* n = nodes[i];
        insert(n);
    }
    assert(isSorted());
}

std::size_t PriorityQueue::size() const noexcept {
    return items_.size();
}

bool PriorityQueue::empty() const noexcept {
    return items_.empty();
}

// Min accessors (MIN = items_.back() under our ordering)
TreeNode* PriorityQueue::findMin() const noexcept {
    // nullptr if empty
    if (items_.empty())
        return nullptr;
    return items_.back();
}

// remove+return min, or nullptr
TreeNode* PriorityQueue::extractMin() noexcept {
    if (items_.empty())
        return nullptr;
    TreeNode* min = items_.back();
    items_.pop_back();
    return min;
}

// remove min if present
void PriorityQueue::deleteMin() noexcept {
        if (!items_.empty())
            items_.pop_back();
}

// Insert while maintaining the invariant (O(N) due to shifting)
// Stores the pointer without taking ownership.
void PriorityQueue::insert(TreeNode* node) {
    items_.push_back(node);
    std::size_t i = items_.size() - 1;

    // insertion sort using higherPriority()
    while (i > 0 && higherPriority(items_[i], items_[i - 1])) {
        std::swap(items_[i], items_[i - 1]);
        --i;
    }
    // assert(isSorted()); For testing
}

// Debug printing
void PriorityQueue::print(std::ostream& os) const {
    os << "[";
    for (std::size_t i = 0; i < items_.size(); ++i) {
        const TreeNode* t = items_[i];
        os << "(" << t->getWord() << "," << t->getFrequency() << ")";
        if (i + 1 < items_.size()) os << ", ";
    }
    os << "]";
}

// Invariant: vector: items_ is kept sorted by HigherPriority(a,b)
// i.e., (freq desc, key_word asc). Therefore the MIN is items_.back().
// Ownership: items_ does NOT own the pointers.

// a before b?
bool PriorityQueue::higherPriority(const TreeNode* a, const TreeNode* b) noexcept {
    if (a->getFrequency() != b->getFrequency())
        return a->getFrequency() > b->getFrequency(); // higher freq first
    return a->getWord() < b->getWord(); // tie: smaller key_word first
}

// for assertions/tests only
bool PriorityQueue::isSorted() const {
    for (std::size_t i = 1; i < items_.size(); ++i) {
        if (higherPriority(items_[i], items_[i - 1]))
            return false;
    }
    return true;
}