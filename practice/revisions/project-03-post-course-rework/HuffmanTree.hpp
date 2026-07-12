// ===============================================================
// File:    HuffmanTree.hpp
// Project: Project_03_Meyer_GPT_Edit
// Author:  Will Meyer
// Date:    2025-11-09
// Purpose: Public interface for the HuffmanTree
//          - Build from (word,count) pairs
//          - Emit codebook (assignCodes / writeHeader)
//          - Encode tokens to bitstring (.code)
// ===============================================================

#ifndef IMPLEMENTATION_HUFFMANTREE_H
#define IMPLEMENTATION_HUFFMANTREE_H

// ---------------------------------------------------------------
// Section: Includes & Forward Decls
// ---------------------------------------------------------------
#include "utils.hpp"
#include <vector>
#include <string>
#include <iosfwd>

struct TreeNode;

// ---------------------------------------------------------------
// Section: Class Declaration
// ---------------------------------------------------------------
class HuffmanTree {
public:
    // ------------------------- Construction --------------------
    HuffmanTree() = default;
    ~HuffmanTree() noexcept;                      // deletes entire Huffman tree

    // Non-copyable; movable (tree owns nodes)
    HuffmanTree(const HuffmanTree&) = delete;
    HuffmanTree& operator=(const HuffmanTree&) = delete;
    HuffmanTree(HuffmanTree&&) noexcept = default;
    HuffmanTree& operator=(HuffmanTree&&) noexcept = default;

    // --------------------------- Factory -----------------------
    // Build from BST output (lexicographic vector of (word, count)).
    static HuffmanTree buildFromCounts(
        const std::vector<std::pair<std::string,int>>& counts
    );

    // -------------------- Codebook & I/O API -------------------
    // Build a vector of (word, code) pairs by traversing the Huffman tree
    // (left=0, right=1; visit left before right).
    void assignCodes(std::vector<std::pair<std::string,std::string>>& out) const;

    // Header writer (pre-order over leaves; "word<space>code"; newline at end).
    error_type writeHeader(std::ostream& os) const;

    // Encode a sequence of tokens using the codebook derived from this tree.
    // Writes ASCII '0'/'1' and wraps lines to wrap_cols (80 by default).
    error_type encode(const std::vector<std::string>& tokens,
                      std::ostream& os_bits,
                      int wrap_cols = 80) const;

private:
    // ----------------------------- Data ------------------------
    TreeNode* root_ = nullptr; // owns the full Huffman tree

    // --------------------------- Helpers -----------------------
    static void destroy(TreeNode* n) noexcept;

    static void assignCodesDFS(const TreeNode* n,
                               std::string& prefix,
                               std::vector<std::pair<std::string,std::string>>& out);

    static void writeHeaderPreorder(const TreeNode* n,
                                    std::ostream& os,
                                    std::string& prefix);
};

#endif // IMPLEMENTATION_HUFFMANTREE_H
