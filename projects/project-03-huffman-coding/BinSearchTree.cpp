//
// Created by Will H Meyer on 10/11/25.
//

#include "BinSearchTree.hpp"


#include <algorithm>
#include <optional>
#include <string_view>
#include <vector>

#include "TreeNode.hpp"


BinSearchTree::~BinSearchTree() {
    // calls destroy(root_)
    destroy(root_);
}

// Insert 'word'; if present, increment its count.
void BinSearchTree::insert(const std::string& word) {
    root_ = insertHelper(root_, word);
}

// Convenience: loop over insert(word) for each token.
void BinSearchTree::bulkInsert(const std::vector<std::string>& words) {
    for (std::size_t i = 0; i < words.size(); ++i) {
        const std::string& w = words[i];
        TreeNode* node = findNode(root_, w);
        if (node == nullptr) {
            // not present → insert with freq=1
            root_ = insertHelper(root_, w);
        } else {
            // present → increment frequency
            node->incFrequency();
            // std::cout << "Incremented: " << w << " -> " << node->getFrequency() << '\n';
        }
    }
}

// Queries
bool BinSearchTree::contains(std::string_view word) const noexcept {
    if (findNode(root_, word)) {
        return true;
    }
    return false;
}

std::optional<int> BinSearchTree::countOf(std::string_view word) const noexcept {
    const TreeNode* node = findNode(root_, word);
    if (node == nullptr) {
        return std::nullopt;
    }
    return node->getFrequency();
}

// In-order traversal (word-lex order) -> flat list for next stage
void BinSearchTree::inorderCollect(std::vector<std::pair<std::string,int>>& out) const {
    out.clear(); // clear the vector
    inorderHelper(root_, out);
}

// Metrics
std::size_t BinSearchTree::size() const noexcept {
    // distinct words
    return sizeHelper(root_);
}

unsigned BinSearchTree::height() const noexcept {
    // empty tree = 0
    return heightHelper(root_);

}

// Helpers
void BinSearchTree::destroy(TreeNode* node) noexcept {
    if (!node)
        return;
    destroy(node->getLeft());
    destroy(node->getRight());
    delete node;
}

TreeNode* BinSearchTree::insertHelper(TreeNode* node, const std::string& word) {
    if (node == nullptr) {
        node = new TreeNode(word);
        return node;
    }
    if (word < node->getWord())
        node->setLeft(insertHelper(node->getLeft(), word));
    else if (word > node->getWord())
        node->setRight(insertHelper(node->getRight(), word));

    return node;
}

// non const findNode for bulkInsert
TreeNode* BinSearchTree::findNode(TreeNode* node, std::string_view word) noexcept {
    if (node == nullptr)
        return nullptr;
    if (node->getWord() == word)
        return node;
    if (word < node->getWord())
        return findNode(node->getLeft(),  word);
    return findNode(node->getRight(), word);
}

const TreeNode* BinSearchTree::findNode(const TreeNode* node, std::string_view word) noexcept {
    if (node == nullptr)
        return nullptr;
    if (node->getWord() == word)
        return node;
    if (word < node->getWord())
        return findNode(node->getLeft(),  word);
    return findNode(node->getRight(), word);
}

void BinSearchTree::inorderHelper(const TreeNode* node,
                          std::vector<std::pair<std::string,int>>& out) {
    if (node == nullptr)
        return;
    inorderHelper(node->getLeft(), out);
    out.emplace_back(node->getWord(), node->getFrequency());
    inorderHelper(node->getRight(), out);
}

std::size_t BinSearchTree::sizeHelper(const TreeNode* node) noexcept {
    if (node == nullptr)
        return 0;
    size_t leftSize = sizeHelper(node->getLeft());
    size_t rightSize = sizeHelper(node->getRight());
    return 1 + leftSize + rightSize;
}

unsigned BinSearchTree::heightHelper(const TreeNode* node) noexcept {
    if (node == nullptr)
        return 0;
    return 1 + std::max(heightHelper(node->getLeft()), heightHelper(node->getRight()));
}