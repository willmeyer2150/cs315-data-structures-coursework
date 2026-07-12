//
// Created by Will H Meyer on 9/30/25.
//

#ifndef CLASS_TREENODE_TREENODE_H
#define CLASS_TREENODE_TREENODE_H
#include <vector>

// Defines a class named TreeNode, which will represent each node in a binary search tree
class TreeNode {
public:
    // Constructor: Initializes the node's value (v_) with v
    // Sets both left and right pointers to nullptr (no children yet)
//    TreeNode(int v) : v_{v}, left{nullptr}, right{nullptr} {}
    TreeNode(int v, TreeNode* left = nullptr, TreeNode* right = nullptr);


    int value() {return v_;}    // A getter that reterns the value stored in the node
    TreeNode* leftSubtree() {return left;}      // Returns a pointer to the node's left child
    TreeNode* rightSubtree() {return right;}    // Returns a pointer to the nodes' right child
    void leftSubtree(TreeNode* node) {left = node;}     // A setter that assigns a new left child
    void rightSubtree(TreeNode* node) {right = node;}   // A setter that assigns a new right child

    int sumOfLeftLeaves(TreeNode* root);
    int inorderPredecessorValue(TreeNode* node);


    bool hasRootToLeafSum(TreeNode* node, int sum);
    TreeNode* bstFromSortedList(const std::vector<int>& v, int leftIdx, int rightIdx);



// Members that can not be accessed outside this class
private:
    int v_; // the data stored in this node
    TreeNode* left; // pointer to the left child
    TreeNode* right; // pointer to the right child

};


#endif //CLASS_TREENODE_TREENODE_H