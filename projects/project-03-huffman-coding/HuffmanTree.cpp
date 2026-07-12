//
// Created by Will H Meyer on 10/21/25.
// HuffmanTree.cpp - build the tree, assign codes, write header and encode bitstream.
//

#include "HuffmanTree.hpp"

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "TreeNode.hpp"
#include "PriorityQueue.hpp"
#include "utils.hpp"

// Build from BST output (lexicographic vector of (word, count)).
// Precondition: counts may be empty. If present, counts[i].second > 0
// Returns HuffmanTree with root_ set or nullptr if empty
HuffmanTree HuffmanTree::buildFromCounts(const std::vector<std::pair<std::string,int>>& counts) {
    HuffmanTree ht;

    // Empty input = empty tree
    if (counts.empty()) {
        ht.root_ = nullptr;
        return ht;
    }
    std::vector<TreeNode*> leaves;
    leaves.reserve(counts.size());


    // Create heap leaves from word/freq pairs
    for (size_t i = 0; i < counts.size(); ++i) {
        const std::string& word = counts[i].first;
        int freq = counts[i].second;

        leaves.push_back(new TreeNode(word, freq));
    }

    // Access PQ interface with new pq
    PriorityQueue pq(leaves);

    // Print the min-Heap for debugging
    // std::cout << "Initial heap: ";
    // pq.print(std::cout);
    // std::cout << "\n";

    // If only 1 found, that node becomes root
    if (pq.size() == 1) {
        ht.root_ = pq.extractMin();
        return ht;
    }

    // Loop while queue has at least 2 items
    // Huffman Tree combination of two min, merge them and reinsert into tree
    while (pq.size() > 1) {
        TreeNode* a = pq.extractMin();
        TreeNode* b = pq.extractMin();

        // Sum frequencies, word field indicates the tie breaker
        TreeNode* parent = new TreeNode(/*word*/"", /*freq*/ a->getFrequency() + b->getFrequency());
        parent->setWord(std::min(a->getWord(), b->getWord()));
        parent->setLeft(a);
        parent->setRight(b);

        pq.insert(parent);
    }

    // Remaining node is the root of the tree.
    ht.root_ = pq.extractMin();  // last remaining node
    return ht;
}


// deletes the entire Huffman tree
HuffmanTree::~HuffmanTree() {
    destroy(root_);
    root_ = nullptr;
}


// 'out' is filled by a vector of (word, code) pairs by traversing the Huffman tree
// (left=0, right=1; visit left before right).
void HuffmanTree::assignCodes(std::vector<std::pair<std::string,std::string>>& out) const {
    if (root_ == nullptr) {
        return;
    }
    out.clear();
    std::string prefix;
    assignCodesDFS(root_, prefix, out);
}


// Header writer to 'os' (pre-order over leaves; "word<space>code"; newline at end).
// Returns NO_ERROR on success
// Returns FAILED_TO_WRITE_FILE with stream errors
error_type HuffmanTree::writeHeader(std::ostream& os) const {
    if (!os) {
        return UNABLE_TO_OPEN_FILE_FOR_WRITING;
    }
    if (root_ == nullptr) {
        return NO_ERROR;
    }

    std::string prefix;
    writeHeaderPreorder(root_, os, prefix);

    if (os.fail()) {
        return FAILED_TO_WRITE_FILE;
    }
    return NO_ERROR;
}


// Encode a sequence of tokens using the codebook derived from this tree.
// Writes ASCII '0'/'1' and wraps lines to wrap_cols (80 by default).
// Returns Errors:
// * FAILED_TO_WRITE_FILE on stream
// * ERR_TYPE_NOT_FOUND if a token is missing from the codebook or if the tree is empty
error_type HuffmanTree::encode(const std::vector<std::string>& tokens,
                  std::ostream& os_bits,
                  int wrap_cols) const {
    // check output stream for error
    if (!os_bits) {
        return FAILED_TO_WRITE_FILE;
    }

    if (root_ == nullptr) {
        return ERR_TYPE_NOT_FOUND;
    }

    // ensure wrap_cols = 80 by default
    if (wrap_cols <= 0) {
        wrap_cols = 80;
    }

    // Create a vector of word/count pairs and fill it to begin building codebook
    std::vector<std::pair<std::string,std::string>> wcPairs;
    assignCodes(wcPairs);

    // Create a map for the codebook
    std::unordered_map<std::string,std::string> codebook;
    for (size_t i = 0; i < wcPairs.size(); ++i) {
        codebook.emplace(wcPairs[i].first, wcPairs[i].second);
    }

    // Tracks column count for line wrapping
    int col = 0;

    // loop through each token and emit codes
    for (size_t i = 0; i < tokens.size(); ++i) {
        const std::string& word = tokens[i];

        // lookup the code using iterator
        // return error if not found
        auto it = codebook.find(word);
        if (it == codebook.end()) {
            return ERR_TYPE_NOT_FOUND;
        }
        // retrieve the code via iterator
        const std::string& code = it->second;

        // write the code to the output stream with proper wrapping
        for (size_t j= 0; j < code.size(); ++j) {
            os_bits << code[j];
            if (!os_bits) {
                return FAILED_TO_WRITE_FILE;
            }

            // Output newline when wrap_cols = 80
            ++col;
            if (col == wrap_cols) {
                os_bits << '\n';
                if (!os_bits) {
                    return FAILED_TO_WRITE_FILE;
                }
                col = 0;
            }
        }
    }
    // Final newline
    os_bits << "\n";
    if (!os_bits) {
        return FAILED_TO_WRITE_FILE;
    }
    return NO_ERROR;
}


// helpers (decl only; defs in .cpp)

// Post-order delete the entire tree
void HuffmanTree::destroy(TreeNode* n) noexcept {
    if (!n)
        return;
    destroy(n->getLeft());
    destroy(n->getRight());
    delete n;
}


// DFS code assignment. Appends '0' for left '1' for right to std::string prefix.
// When leaf found, emits word/code assignment
void HuffmanTree::assignCodesDFS(const TreeNode* n,
                           std::string& prefix,
                           std::vector<std::pair<std::string,std::string>>& out) {
    if (n == nullptr)
        return;
    // Case 1: If it is a leaf (no children)
    if (n->getLeft() == nullptr && n->getRight() == nullptr) {
        const std::string& code = prefix.empty() ? "0" : prefix;
        out.emplace_back(n->getWord(), code);
        return;
    }

    prefix.push_back('0');
    assignCodesDFS(n->getLeft(), prefix, out);
    prefix.pop_back();

    prefix.push_back('1');
    assignCodesDFS(n->getRight(), prefix, out);
    prefix.pop_back();
}


// Preorder traversal that writes word code for each leaf into 'os'
// Same as logic for assignCodesDFS, but streams the output instead of inserting into vector.
void HuffmanTree::writeHeaderPreorder(const TreeNode* n, std::ostream& os,
                                std::string& prefix) {
    if (n == nullptr)
        return;
    if (n->getLeft() == nullptr && n->getRight() == nullptr) {
        const std::string& code = prefix.empty() ? "0" : prefix;
        os << n->getWord() << " " << code << "\n";
        return;
    }

    prefix.push_back('0');
    writeHeaderPreorder(n->getLeft(), os, prefix);
    prefix.pop_back();

    prefix.push_back('1');
    writeHeaderPreorder(n->getRight(), os, prefix);
    prefix.pop_back();
}