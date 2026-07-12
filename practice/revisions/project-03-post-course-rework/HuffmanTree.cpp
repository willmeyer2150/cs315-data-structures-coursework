// ===============================================================
// File:    HuffmanTree.cpp
// Project: Project_03_Meyer_GPT_Edit
// Author:  Will Meyer
// Date:    2025-11-09
// Purpose: Implementation of HuffmanTree
//          - Build tree from (word,count)
//          - Assign codes (DFS)
//          - Write header (.hdr) and encode (.code)
// ===============================================================

#include "HuffmanTree.hpp"

// ---------------------------------------------------------------
// Section 1: Includes
// ---------------------------------------------------------------
#include <algorithm>
#include <unordered_map>
#include <vector>

#include "TreeNode.hpp"
#include "PriorityQueue.hpp"
#include "utils.hpp"

// ---------------------------------------------------------------
// Section 2: Factory / Construction / Destruction
// ---------------------------------------------------------------

// Build from BST output (lexicographic vector of (word, count)).
// Precondition: counts may be empty. If present, counts[i].second > 0
// Returns HuffmanTree with root_ set or nullptr if empty
HuffmanTree HuffmanTree::buildFromCounts(
    const std::vector<std::pair<std::string,int>>& counts)
{
    HuffmanTree ht;

    // Empty input = empty tree
    if (counts.empty()) {
        ht.root_ = nullptr;
        return ht;
    }

    // Create leaves from word/freq pairs
    std::vector<TreeNode*> leaves;
    leaves.reserve(counts.size());
    for (const auto& kv : counts) {
        const std::string& word = kv.first;
        const int          freq = kv.second;
        leaves.emplace_back(new TreeNode(word, freq));
    }

    // Build min-heap
    PriorityQueue pq(leaves);

    // Single symbol edge case
    if (pq.size() == 1) {
        ht.root_ = pq.extractMin();
        return ht;
    }

    // Combine two minimums each step until one remains
    while (pq.size() > 1) {
        TreeNode* a = pq.extractMin();
        TreeNode* b = pq.extractMin();

        // Parent accumulates frequency; word field is tiebreak (min of children)
        TreeNode* parent = new TreeNode(/*word*/"", /*freq*/ a->getFrequency() + b->getFrequency());
        parent->setWord(std::min(a->getWord(), b->getWord()));
        parent->setLeft(a);
        parent->setRight(b);

        pq.insert(parent);
    }

    // Remaining node is the root
    ht.root_ = pq.extractMin();
    return ht;
}

// deletes the entire Huffman tree
HuffmanTree::~HuffmanTree() noexcept {
    destroy(root_);
    root_ = nullptr;
}

// ---------------------------------------------------------------
// Section 3: Public API (assignCodes / writeHeader / encode)
// ---------------------------------------------------------------

// Fill 'out' with (word, code) by traversing the Huffman tree
// (left=0, right=1; visit left before right).
void HuffmanTree::assignCodes(std::vector<std::pair<std::string,std::string>>& out) const {
    if (root_ == nullptr) return;
    out.clear();
    std::string prefix;
    assignCodesDFS(root_, prefix, out);
}

// Header writer to 'os' (pre-order over leaves; "word<space>code"; newline at end).
// Returns NO_ERROR on success; FAILED_TO_WRITE_FILE on stream errors
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

// Encode tokens using the codebook derived from this tree.
// Writes ASCII '0'/'1' and wraps to wrap_cols (default 80).
// Errors:
// * FAILED_TO_WRITE_FILE on stream errors
// * ERR_TYPE_NOT_FOUND if a token is missing from the codebook or tree is empty
error_type HuffmanTree::encode(const std::vector<std::string>& tokens,
                               std::ostream& os_bits,
                               int wrap_cols) const
{
    // Validate output stream and presence of a tree
    if (!os_bits) return FAILED_TO_WRITE_FILE;
    if (root_ == nullptr) return ERR_TYPE_NOT_FOUND;

    if (wrap_cols <= 0) wrap_cols = 80;

    // Build codebook (word -> code)
    std::vector<std::pair<std::string,std::string>> wordCodePairs;
    assignCodes(wordCodePairs);

    std::unordered_map<std::string,std::string> codebook(wordCodePairs.begin(), wordCodePairs.end());

    // Emit bits with wrapping
    int col = 0;
    for (const auto& word : tokens) {
        auto it = codebook.find(word);
        if (it == codebook.end()) return ERR_TYPE_NOT_FOUND;

        const std::string& code = it->second;
        for (char bit : code) {
            os_bits.put(bit);
            if (!os_bits) return FAILED_TO_WRITE_FILE;

            if (++col == wrap_cols) {
                os_bits.put('\n');
                if (!os_bits) return FAILED_TO_WRITE_FILE;
                col = 0;
            }
        }
    }

    // Final newline
    os_bits.put('\n');
    if (!os_bits) return FAILED_TO_WRITE_FILE;

    return NO_ERROR;
}

// ---------------------------------------------------------------
// Section 4: Private Helpers (definitions)
// ---------------------------------------------------------------

// Post-order delete the entire tree
void HuffmanTree::destroy(TreeNode* n) noexcept {
    if (!n) return;
    destroy(n->getLeft());
    destroy(n->getRight());
    delete n;
}

// DFS code assignment. Appends '0' for left, '1' for right to prefix.
// When a leaf is found, emits (word,code) into 'out'.
void HuffmanTree::assignCodesDFS(const TreeNode* n,
                                 std::string& prefix,
                                 std::vector<std::pair<std::string,std::string>>& out) {
    if (n == nullptr) return;

    // Leaf?
    if (n->getLeft() == nullptr && n->getRight() == nullptr) {
        const std::string code = prefix.empty() ? std::string("0") : prefix;
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

// Preorder traversal: write "word code\n" for each leaf to 'os'.
void HuffmanTree::writeHeaderPreorder(const TreeNode* n,
                                      std::ostream& os,
                                      std::string& prefix) {
    if (n == nullptr) return;

    if (n->getLeft() == nullptr && n->getRight() == nullptr) {
        const std::string code = prefix.empty() ? std::string("0") : prefix;
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
