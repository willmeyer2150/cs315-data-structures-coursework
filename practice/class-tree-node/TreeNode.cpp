//
// Created by Will H Meyer on 9/30/25.
//

#include "TreeNode.h"

TreeNode* TreeNode::bstFromSortedList(const std::vector<int>& v, int leftIdx, int rightIdx) {
    if (leftIdx < rightIdx) {
        return nullptr;
    }

    int mid = leftIdx + (rightIdx - leftIdx) / 2;
    TreeNode* root = new TreeNode(v[mid]);

    root->leftSubtree(bstFromSortedList(v, leftIdx, mid - 1));
    root->rightSubtree(bstFromSortedList(v, mid + 1, rightIdx));
    return root;
}

bool TreeNode::hasRootToLeafSum(TreeNode* node, int sum)
{
    if (node == nullptr) {
        return false;
    }
    sum -= node->value();
    if (node->leftSubtree() == nullptr && node->rightSubtree() == nullptr) {
        return sum == 0;
    }
    return hasRootToLeafSum(node->leftSubtree(), sum) || hasRootToLeafSum(node->rightSubtree(), sum);
}

int TreeNode::sumOfLeftLeaves(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }

    int sum = 0;
    if (root->leftSubtree() == nullptr && root->rightSubtree() == nullptr) {
        sum = sum + root->value();
    }

    return sum + (sumOfLeftLeaves(root->leftSubtree()) + sumOfLeftLeaves(root->rightSubtree()));
}

int sumOfLeftLeaves(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }

    int sum = 0;
    TreeNode* leftChild = root->leftSubtree();

    // If the left child exists and is a leaf
    if (leftChild != nullptr &&
        leftChild->leftSubtree() == nullptr &&
        leftChild->rightSubtree() == nullptr) {
        sum = sum + leftChild->value();
        }

    int leftSum = sumOfLeftLeaves(root->leftSubtree());
    int rightSum = sumOfLeftLeaves(root->rightSubtree());

    return sum + leftSum + rightSum;
}


bool areIdentical(TreeNode* first, TreeNode* second) {
    if (first == nullptr && second == nullptr) {
        return true;
    }

    if (first == nullptr || second == nullptr) {
        return false;
    }

    bool valuesMatch = (first->value() == second->value());
    bool leftMatch = areIdentical(first->leftSubtree(), second->leftSubtree());
    bool rightMatch = areIdentical(first->rightSubtree(), second->rightSubtree());

    return valuesMatch && leftMatch && rightMatch;
}

int maxDepth(TreeNode* root);  // assume defined elsewhere

int treeDiameter(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }

    int leftHeight = maxDepth(root->leftSubtree());
    int rightHeight = maxDepth(root->rightSubtree());

    int leftDiameter = treeDiameter(root->leftSubtree());
    int rightDiameter = treeDiameter(root->rightSubtree());

    int throughRoot = leftHeight + rightHeight + 1;

    if (throughRoot > leftDiameter && throughRoot > rightDiameter) {
        return throughRoot;
    } else if (leftDiameter > rightDiameter) {
        return leftDiameter;
    } else {
        return rightDiameter;
    }
}

int TreeNode::inorderPredecessorValue(TreeNode* node) {
    if (node == nullptr || node->leftSubtree() == nullptr)
        throw std::runtime_error("No left child; predecessor undefined");

    if (node->leftSubtree()->rightSubtree() != nullptr)
        return inorderPredecessorValue(node->leftSubtree()->rightSubtree());

    return node->leftSubtree()->value();
}

