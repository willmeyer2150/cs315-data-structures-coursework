//
// Created by Ali Kooshesh on 10/1/25.
//

#ifndef BINSEARCHTREESTUDENTFILES_TREENODE_HPP
#define BINSEARCHTREESTUDENTFILES_TREENODE_HPP

class TreeNode {
public:
    // Constructors
    TreeNode( int n ): left(nullptr), right(nullptr), data(n) {}
    ~TreeNode() {
        leftSubtree(nullptr);
        rightSubtree(nullptr);
    }

    TreeNode *leftSubtree() { return left; }
    TreeNode *rightSubtree() { return right; }

    void leftSubtree( TreeNode *newLeft ) { left = newLeft; }
    void rightSubtree(TreeNode *newRight) { right = newRight; }

    int& value() { return data; }

private:
    TreeNode *left, *right;
    int data;
};

#endif //BINSEARCHTREESTUDENTFILES_TREENODE_HPP