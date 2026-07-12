// ===============================================================
// File:    TreeNode.hpp
// Project: Project_03_Meyer_GPT_Edit
// Author:  Will Meyer
// Date:    2025-11-09
// Purpose: Node for BST and Huffman tree.
//          Stores (word, frequency) and raw child pointers.
// ===============================================================

#ifndef IMPLEMENTATION_TREENODE_H
#define IMPLEMENTATION_TREENODE_H

// ---------------------------------------------------------------
// Section: Includes
// ---------------------------------------------------------------
#include <iostream> // for print()
#include <string>

// ---------------------------------------------------------------
// Section: Class Declaration
// ---------------------------------------------------------------
class TreeNode {
public:
    // ------------------------- Ctors ---------------------------
    // word+freq
    TreeNode(const std::string& str, int num)
        : frequency_(num), word_(str), left_(nullptr), right_(nullptr) {}

    // word, default freq=1
    TreeNode(const std::string& str)
        : frequency_(1), word_(str), left_(nullptr), right_(nullptr) {}

    // ------------------------ Accessors ------------------------
    int                 getFrequency() const noexcept { return frequency_; }
    const std::string&  getWord()     const noexcept { return word_; }

    // ------------------------ Mutators -------------------------
    void setFrequency(int num)                 noexcept { frequency_ = num; }
    void setWord(const std::string& str)                 { word_ = str; }

    // --------------------- Child Pointers ----------------------
    TreeNode* getLeft()  const noexcept { return left_; }
    TreeNode* getRight() const noexcept { return right_; }

    void setLeft(TreeNode* left)   noexcept { left_  = left; }
    void setRight(TreeNode* right) noexcept { right_ = right; }

    void incFrequency() noexcept { ++frequency_; }

    // -------------------------- Debug --------------------------
    void print() const {
        std::cout << "(" << getWord() << ", " << getFrequency() << ")" << std::endl;
    }

private:
    // -------------------------- Data ---------------------------
    int         frequency_ = 1;  // frequency count
    std::string word_;
    TreeNode*   left_  = nullptr;
    TreeNode*   right_ = nullptr;
};

#endif // IMPLEMENTATION_TREENODE_H
