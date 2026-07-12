// ===============================================================
// File:    BinSearchTree.cpp
// Project: Project_03_Meyer_GPT_Edit
// Author:  Will Meyer
// Date:    2025-11-09
// Purpose: Implementation of a BST keyed by std::string with
//          frequency counts; supports bulkInsert, queries, and
//          in-order collection for downstream Huffman stage.
// ===============================================================

#include "BinSearchTree.hpp"

// ---------------------------------------------------------------
// Section 1: Includes
// ---------------------------------------------------------------
#include <algorithm>
#include <string>
#include <string_view>
#include <vector>
#include "TreeNode.hpp"

// ---------------------------------------------------------------
// Section 2: Construction / Destruction
// ---------------------------------------------------------------
BinSearchTree::~BinSearchTree() noexcept {
    destroy(root_);
    root_ = nullptr;
}

// ---------------------------------------------------------------
// Section 3: Modifiers
// ---------------------------------------------------------------
void BinSearchTree::insert(const std::string& word) {
    root_ = insertHelper(root_, word);
}

void BinSearchTree::bulkInsert(const std::vector<std::string>& words) {
    for (const auto& w : words) {
        // If already present, increment; otherwise insert new node with freq=1
        if (TreeNode* node = findNode(root_, w)) {
            node->incFrequency();
        } else {
            root_ = insertHelper(root_, w);
        }
    }
}

// ---------------------------------------------------------------
// Section 4: Queries
// ---------------------------------------------------------------
bool BinSearchTree::contains(std::string_view word) const noexcept {
    return findNode(root_, word) != nullptr;
}

std::optional<int> BinSearchTree::countOf(std::string_view word) const noexcept {
    if (const TreeNode* node = findNode(root_, word)) {
        return node->getFrequency();
    }
    return std::nullopt;
}

// ---------------------------------------------------------------
// Section 5: Traversal & Collection
// ---------------------------------------------------------------
void BinSearchTree::inorderCollect(std::vector<std::pair<std::string,int>>& out) const {
    out.clear();
    inorderHelper(root_, out);
}

// ---------------------------------------------------------------
// Section 6: Metrics
// ---------------------------------------------------------------
std::size_t BinSearchTree::size() const noexcept {
    return sizeHelper(root_);
}

unsigned BinSearchTree::height() const noexcept {
    return heightHelper(root_);
}

// ---------------------------------------------------------------
// Section 7: Helpers (private)
// ---------------------------------------------------------------
void BinSearchTree::destroy(TreeNode* node) noexcept {
    if (!node) return;
    destroy(node->getLeft());
    destroy(node->getRight());
    delete node;
}

TreeNode* BinSearchTree::insertHelper(TreeNode* node, const std::string& word) {
    if (node == nullptr) {
        return new TreeNode(word);           // ctor should set freq=1
    }
    if (word < node->getWord()) {
        node->setLeft(insertHelper(node->getLeft(), word));
    } else if (word > node->getWord()) {
        node->setRight(insertHelper(node->getRight(), word));
    } else {
        // Equal: word already present → increment frequency
        node->incFrequency();
    }
    return node;
}

// Non-const findNode (used by bulkInsert for in-place frequency inc)
TreeNode* BinSearchTree::findNode(TreeNode* node, std::string_view word) noexcept {
    if (node == nullptr) return nullptr;
    if (node->getWord() == word) return node;
    if (word < node->getWord())  return findNode(node->getLeft(),  word);
    return findNode(node->getRight(), word);
}

// Const overload for read-only queries
const TreeNode* BinSearchTree::findNode(const TreeNode* node, std::string_view word) noexcept {
    if (node == nullptr) return nullptr;
    if (node->getWord() == word) return node;
    if (word < node->getWord())  return findNode(node->getLeft(),  word);
    return findNode(node->getRight(), word);
}

void BinSearchTree::inorderHelper(const TreeNode* node,
                                  std::vector<std::pair<std::string,int>>& out) {
    if (node == nullptr) return;
    inorderHelper(node->getLeft(), out);
    out.emplace_back(node->getWord(), node->getFrequency());
    inorderHelper(node->getRight(), out);
}

std::size_t BinSearchTree::sizeHelper(const TreeNode* node) noexcept {
    if (node == nullptr) return 0;
    return 1 + sizeHelper(node->getLeft()) + sizeHelper(node->getRight());
}

unsigned BinSearchTree::heightHelper(const TreeNode* node) noexcept {
    if (node == nullptr) return 0;
    const unsigned hl = heightHelper(node->getLeft());
    const unsigned hr = heightHelper(node->getRight());
    return 1 + (hl > hr ? hl : hr);
}
