//
// Created by Ali Kooshesh on 10/1/25.
//
// Will Meyer
// Collaborated with Caleb Clements

#include <iostream>
#include <algorithm>
#include "BinSearchTree.hpp"
#include "TreeNode.hpp"

BinSearchTree::BinSearchTree(): root{nullptr} {}

TreeNode *BinSearchTree::insert( TreeNode *root, int v ) {
    if( root == nullptr )
        return new TreeNode( v );
    if( root->value() < v )
        root->rightSubtree( insert( root->rightSubtree(), v ) );
    else
        root->leftSubtree( insert( root->leftSubtree(), v ) );
    return root;
}

bool BinSearchTree::insert(int v) {
    // Insert v in the tree if it is not already a member.
    // Return true if the value was indeed inserted into the tree.
    // Otherwise, return false.

    if( ! find(v) ) {
        root = insert(root, v);
        return true;
    }
    return false;
}

// Recursive size() helper function
int BinSearchTree::size(TreeNode* root) {
    // Write this function first!
    if ( root == nullptr ) {
        return 0;
    }
    return 1 + size(root->leftSubtree()) + size(root->rightSubtree());
}

// public size() function for main()
int BinSearchTree::size() {
    return size(root);
}

// Recursive find() helper function
bool BinSearchTree::find(TreeNode* root, int key) {
    if (root == nullptr)
        return false;
    if (root->value() == key)
        return true;
    if (key < root->value())
        return find(root->leftSubtree(), key);
    return find(root->rightSubtree(), key);
}

// public find() function for main()
bool BinSearchTree::find(int key) {
    // You need to write a recursive implementation for this function.
    // Right now, it returns false so that insert can do its job.
    // That means, it will add duplicates to the tree, which is not desirable.
    return find(root, key);
}

// public iterFind() for main()
bool BinSearchTree::iterFind(int key) {
    if (root == nullptr)
        return false;
    TreeNode* temp = root;
    while (temp != nullptr && temp->value() != key) {
        if (temp->value() > key)
            temp = temp->leftSubtree();
        else
            temp = temp->rightSubtree();
    }
    return temp != nullptr;
}

// Recursive inOrderListings() helper function
void BinSearchTree::inorderListing(TreeNode* root) {
    if (root == nullptr)
        return;
    inorderListing(root->leftSubtree());
    std::cout << root->value() << std::endl;
    inorderListing(root->rightSubtree());
}

// public inorderListing() for main()
void BinSearchTree::inorderListing() {
    inorderListing(root);
}

// Recursive maxDepth() helper function
int BinSearchTree::maxDepth(TreeNode* root) {
    if (root == nullptr)
        return 0;
    return 1 + std::max(maxDepth(root->leftSubtree()), maxDepth(root->rightSubtree()));
}

// public maxDepth() for main
int BinSearchTree::maxDepth() {
    return maxDepth(root);
}

// Public iterInsert() function for main()
void BinSearchTree::iterInsert(int key) {
    // if root is empty, make key the root of new tree
    if (root == nullptr) {
        root = new TreeNode(key);
        return;
    }
    // Parent points to root
    TreeNode* parent = nullptr;
    // cur is root
    TreeNode* cur = root;

    while (cur != nullptr){
        parent = cur;               // assign parent to cur
        if (cur->value() == key)    // check if key equals cur
            return;
        else if (cur->value() > key) {  // if key is less than cur
            cur = cur->leftSubtree();   // advance cur down the left subtree
        }
        else {
            cur = cur->rightSubtree();  // otherwise, advance down the right subtree
        }
    }
    if (key < parent->value())      // if key is less than the parent value
        parent->leftSubtree(new TreeNode(key));     // attach new left child
    else
        parent->rightSubtree(new TreeNode(key));    // otherwise, attach new right child
}

// Recursive ~BinSearchTree() helper function
void BinSearchTree::deleteTree(TreeNode* root) {
    if (root == nullptr)
        return;
    deleteTree(root->leftSubtree());
    deleteTree(root->rightSubtree());
    delete root;
}

// Public ~BinSearchTree() for main()
BinSearchTree::~BinSearchTree() {
    // This function should delete every node in the tree.
    // To do that, you will have to recursively traverse the tree, using
    // a post-order traversal.
    deleteTree(root);
    root = nullptr;
}
