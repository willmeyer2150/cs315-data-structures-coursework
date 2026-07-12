//
// Created by Will H Meyer on 10/29/25.
//

#include "HuffmanTree.hpp"

// Reconstructs a Huffman tree from the word/code pairs read in readHeder()
// Pre-condition: Each pair in the header_pairs contains a word/code which connects a word to its binary code
// Post: Returns appropriate error code or NO_ERROR if tree successfully build
error_type HuffmanTree::buildFromHeader(const std::vector<std::pair<std::string, std::string>>& header_pairs) {
    // start with a clean tree
    destroy(root_);
    root_ = nullptr;

    // if vector is empty, return error
    if (header_pairs.empty()) {
        return HDR_EMPTY;
    }

    // initialize new tree with an empty token (word) node
    root_ = new TreeNode("");
    // insert each word/code pair into the tree
    for (const auto& pair : header_pairs) {
        std::string word = pair.first;
        std::string code = pair.second;

        TreeNode* cur = root_;
        // build nodes while moving through code
        for (char c : code) {
            if (cur == nullptr) {
                return HDR_PARSE_ERROR;
            }
            // go left first, create missing node if needed
            if (c == '0') {
                if (cur->getLeft() == nullptr) {
                    cur->setLeft(new TreeNode(""));
                }
                cur = cur->getLeft();
            }
            // go right, create missing node if needed
            else if (c == '1') {
                if (cur->getRight() == nullptr) {
                    cur->setRight(new TreeNode(""));
                }
                cur = cur->getRight();
            }
            // invalid code case
            else {
                return HDR_BAD_CODE_BITS;
            }
        }

        // set the leaf to the word once end of code reached
        if (cur == nullptr) {
            return HDR_PARSE_ERROR;
        }
        cur->setToken(word);
    }

    return NO_ERROR;
}

// decodes an encoded bitstream
// Pre-condition: function is passed a bit stream to decode into the original text.
// Post: If successful, each time a leaf node is reached a word is printed to output stream, otherwise, throw error
error_type HuffmanTree::decode(std::istream& code_stream, std::ostream& out_stream) {
    // check for valid tree
    if (root_ == nullptr) {
        return HDR_EMPTY;
    }

    TreeNode* cur = root_;
    char bit;

    // read the encoded bitsream one char at a time
    while (code_stream.get(bit)) {
        // Skip whitespace
        if (bit == ' ' || bit == '\n' || bit == '\r') {
            continue;
        }

        // Only '0' or '1' are valid
        if (bit != '0' && bit != '1') {
            return HDR_BAD_CODE_BITS;
        }

        // Single leaf case
        if (root_->getLeft() == nullptr && root_->getRight() == nullptr) {
            out_stream << root_->getToken();
            continue;
        }

        // Traverse the tree left or right based on bit value (0 or 1)
        if (bit == '0') {
            cur = cur->getLeft();
        } else { // ch == '1'
            cur = cur->getRight();
        }

        if (cur == nullptr) {
            // Path doesn't exist, throw error
            return HDR_PARSE_ERROR;
        }

        // If we reached a leaf, emit token and reset to root
        if (cur->getLeft() == nullptr && cur->getRight() == nullptr) {
            out_stream << cur->getToken() << std::endl;
            cur = root_;
        }
    }

    // If the tree has branches and we ended mid-path, it's incomplete -- return error
    // Edge case (shouldn't happen)
    if ((root_->getLeft() != nullptr || root_->getRight() != nullptr) && cur != root_) {
        return HDR_PARSE_ERROR;
    }

    return NO_ERROR;
}

void HuffmanTree::destroy(TreeNode* n) noexcept {
    if (!n)
        return;
    destroy(n->getLeft());
    destroy(n->getRight());
    delete n;
}