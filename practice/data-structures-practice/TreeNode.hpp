

#ifndef CLASS_TREENODE_TREENODE_H
#define CLASS_TREENODE_TREENODE_H


class TreeNode {
public:
    TreeNode(int v, TreeNode* left = nullptr, TreeNode* right = nullptr);

    int value() const {return v_;}
    TreeNode* leftSubtree() const {return left;}
    TreeNode* rightSubtree() const {return right;}
    void leftSubtree(TreeNode* node) {left = node;}
    void rightSubtree(TreeNode* node) {right = node;}

    bool hasSymbol() const {return v_ != -1;}
    bool isLeaf() const {return left == nullptr && right == nullptr;}

private:
    int v_;
    TreeNode* left;
    TreeNode* right;
};

#endif //CLASS_TREENODE_TREENODE_H