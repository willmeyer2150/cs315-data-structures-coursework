// ===============================================================
// File:    PriorityQueue.cpp
// Project: Project_03_Meyer_GPT_Edit
// Author:  Will Meyer
// Date:    2025-11-09
// Purpose: Implementation of non-owning priority queue used by
//          HuffmanTree. Keeps items sorted so that MIN is back().
// ===============================================================

#include "PriorityQueue.hpp"

// ---------------------------------------------------------------
// Section 1: Includes
// ---------------------------------------------------------------
#include <cassert>
#include <ostream>
#include <utility>    // std::swap
#include <iostream>   // for std::cout in convenience overload
#include "TreeNode.hpp"

// ---------------------------------------------------------------
// Section 2: Construction
// ---------------------------------------------------------------
PriorityQueue::PriorityQueue(std::vector<TreeNode*> nodes) {
    items_.reserve(nodes.size());
    // Insert one-by-one to preserve invariant (matches original behavior)
    for (TreeNode* n : nodes) {
        insert(n);
    }
    assert(isSorted());
}

// ---------------------------------------------------------------
// Section 3: Observers
// ---------------------------------------------------------------
std::size_t PriorityQueue::size() const noexcept {
    return items_.size();
}

bool PriorityQueue::empty() const noexcept {
    return items_.empty();
}

// Min = items_.back() under our ordering
TreeNode* PriorityQueue::findMin() const noexcept {
    if (items_.empty()) return nullptr;
    return items_.back();
}

TreeNode* PriorityQueue::extractMin() noexcept {
    if (items_.empty()) return nullptr;
    TreeNode* min = items_.back();
    items_.pop_back();
    return min;
}

void PriorityQueue::deleteMin() noexcept {
    if (!items_.empty()) items_.pop_back();
}

// ---------------------------------------------------------------
// Section 4: Modifiers
// ---------------------------------------------------------------
void PriorityQueue::insert(TreeNode* node) {
    items_.push_back(node);
    std::size_t i = items_.size();
    // Insertion sort step (bubble the new element leftwards)
    while (i > 1 && higherPriority(items_[i - 1], items_[i - 2])) {
        std::swap(items_[i - 1], items_[i - 2]);
        --i;
    }
    // assert(isSorted());  // Uncomment for runtime checking
}

// ---------------------------------------------------------------
// Section 5: Debug
// ---------------------------------------------------------------
void PriorityQueue::print(std::ostream& os) const {
    os << "[";
    for (std::size_t i = 0; i < items_.size(); ++i) {
        const TreeNode* t = items_[i];
        os << "(" << t->getWord() << "," << t->getFrequency() << ")";
        if (i + 1 < items_.size()) os << ", ";
    }
    os << "]";
}

// Convenience overload prints to std::cout
void PriorityQueue::print() const {
    print(std::cout);
}

// ---------------------------------------------------------------
// Section 6: Helpers
// ---------------------------------------------------------------
bool PriorityQueue::higherPriority(const TreeNode* a, const TreeNode* b) noexcept {
    // Higher frequency first
    if (a->getFrequency() != b->getFrequency())
        return a->getFrequency() > b->getFrequency();
    // Tie-break: lexicographically smaller word first
    return a->getWord() < b->getWord();
}

bool PriorityQueue::isSorted() const noexcept {
    if (items_.size() < 2) return true;
    for (std::size_t i = 1; i < items_.size(); ++i) {
        // If current should be before previous, order is broken
        if (higherPriority(items_[i], items_[i - 1])) return false;
    }
    return true;
}
