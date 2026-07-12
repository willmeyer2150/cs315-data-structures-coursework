//
// Created by Will H Meyer on 10/29/25.
//

#include "utils.hpp"
#include "TreeNode.hpp"

#ifndef PROJECT_04_MEYER_HUFFMANTREE_H
#define PROJECT_04_MEYER_HUFFMANTREE_H

class HuffmanTree {
public:
    HuffmanTree() = default;
    ~HuffmanTree() { destroy(root_); root_ = nullptr; }

    error_type buildFromHeader(const std::vector<std::pair<std::string, std::string>>& header_pairs);
    error_type decode(std::istream& code_stream, std::ostream& out_stream);

    // Debug print helper
    // void printTree(TreeNode* node, const std::string& prefix) const {
    //     if (!node) return;
    //
    //     // print this node
    //     std::cout << prefix << (node->getToken().empty() ? "[internal]" : node->getToken()) << "\n";
    //
    //     // go down a level
    //     printTree(node->getLeft(), prefix + " 0-> ");
    //     printTree(node->getRight(), prefix + " 1-> ");
    // }
    //
    // // print the tree
    // void printTree() const {
    //     printTree(root_, "");
    // }

private:
    TreeNode* root_ = nullptr; // owns the full Huffman tree

    // helpers
    static void destroy(TreeNode* n) noexcept;
};


#endif //PROJECT_04_MEYER_HUFFMANTREE_H