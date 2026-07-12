// ===============================================================
// File:    PriorityQueue.hpp
// Project: Project_03_Meyer_GPT_Edit
// Author:  Will Meyer
// Date:    2025-11-09
// Purpose: Non-owning priority queue for TreeNode* used by HuffmanTree.
//          Invariant: items_ kept sorted by higherPriority(a,b)
//          i.e., (freq desc, word asc). Therefore MIN is items_.back().
// ===============================================================

#ifndef IMPLEMENTATION_PRIORITYQUEUE_H
#define IMPLEMENTATION_PRIORITYQUEUE_H

// ---------------------------------------------------------------
// Section: Includes & Forward Decls
// ---------------------------------------------------------------
#include <vector>
#include <iosfwd>   // std::ostream
#include <cstddef>

struct TreeNode;

// ---------------------------------------------------------------
// Section: Class Declaration
// ---------------------------------------------------------------
class PriorityQueue {
public:
    // ------------------------- Construction --------------------
    // Non-owning: does NOT delete the TreeNode* it stores.
    // Takes initial nodes and inserts them maintaining invariant.
    explicit PriorityQueue(std::vector<TreeNode*> nodes);
    ~PriorityQueue() = default;

    // --------------------------- Observers ---------------------
    [[nodiscard]] std::size_t size()  const noexcept;
    [[nodiscard]] bool         empty() const noexcept;

    // Min accessors (MIN == items_.back() under our ordering)
    [[nodiscard]] TreeNode* findMin()   const noexcept;  // nullptr if empty
    TreeNode*               extractMin()      noexcept;  // remove+return min, or nullptr
    void                    deleteMin()       noexcept;  // remove min if present

    // --------------------------- Modifiers ---------------------
    // Insert while maintaining invariant (O(N) due to shifting). Non-owning.
    void insert(TreeNode* node);

    // ----------------------------- Debug ----------------------
    // No default parameter here (avoids pulling <iostream> into header).
    void print(std::ostream& os) const;  // defined in .cpp
    void print() const;                  // convenience overload prints to std::cout

private:
    // -----------------------------------------------------------
    // Invariant & Storage
    // -----------------------------------------------------------
    // Invariant: items_ sorted by higherPriority(a,b)
    //            => (freq desc, word asc). MIN is items_.back().
    // Ownership: items_ does NOT own stored pointers.
    std::vector<TreeNode*> items_;

    // Comparator: true if 'a' should appear before 'b'
    static bool higherPriority(const TreeNode* a, const TreeNode* b) noexcept;

    // For assertions/tests only
    bool isSorted() const noexcept;
};

#endif // IMPLEMENTATION_PRIORITYQUEUE_H
