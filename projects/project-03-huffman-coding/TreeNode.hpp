//
// Created by Will H Meyer on 10/11/25.
//

#include <iostream>
#include <string>

#ifndef IMPLEMENTATION_TREENODE_H
#define IMPLEMENTATION_TREENODE_H


class TreeNode {
public:
    // Constructors
    TreeNode(const std::string& str, int num)
        : frequency_(num), word_(str), left_(nullptr), right_(nullptr) {}

    TreeNode(const std::string& str)
        : frequency_(1), word_(str), left_(nullptr), right_(nullptr) {}

    // Getters for data
    int getFrequency() const { return frequency_; }
    const std::string& getWord() const { return word_; }

    // Setters for data
    void setFrequency(int num) { frequency_ = num; }
    void setWord(const std::string& str) { word_ = str; }

    // Getters and Setters for Children
    TreeNode* getLeft() const { return left_; }
    TreeNode* getRight() const { return right_; }

    void setLeft(TreeNode* left) { left_ = left; }
    void setRight(TreeNode* right) { right_ = right; }

    void incFrequency() { ++frequency_; }

    void print() const {
        std::cout << "(" << getWord() << ", " << getFrequency() << ")" << std::endl;
    }

private:
    int frequency_ = 1;   // for counting frequency
    std::string word_;
    TreeNode* left_;
    TreeNode* right_;
};


#endif //IMPLEMENTATION_TREENODE_H