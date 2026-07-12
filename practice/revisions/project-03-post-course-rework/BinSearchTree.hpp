// ===============================================================
// File:    BinSearchTree.hpp
// Project: Project_03_Meyer_GPT_Edit
// Author:  Will Meyer
// Date:    2025-11-09
// Purpose: BST keyed by word (std::string) storing frequency counts.
//          - bulkInsert(tokens) builds tree, incrementing counts
//          - inorderCollect() emits (word,count) in lex order
//          - height() treats empty as 0
// ===============================================================

#ifndef IMPLEMENTATION_BINSEARCHTREE_H
#define IMPLEMENTATION_BINSEARCHTREE_H

// ---------------------------------------------------------------
// Section: Includes & Forward Decls
// ---------------------------------------------------------------
#include <string>
#include <string_view>
#include <vector>
#include <optional>
#include <cstddef>

struct TreeNode; // defined elsewhere

// ---------------------------------------------------------------
// Section: Class Declaration
// ---------------------------------------------------------------
class BinSearchTree {
public:
    BinSearchTree() = default;
    ~BinSearchTree() noexcept; // calls destroy(root_)

    // --------------------------- Modifiers ---------------------
    // Insert 'word'; if present, increment its count.
    void insert(const std::string& word);

    // Loop over insert(word) or increment existing counts.
    void bulkInsert(const std::vector<std::string>& words);

    // ---------------------------- Queries ----------------------
    [[nodiscard]] bool contains(std::string_view word) const noexcept;
    [[nodiscard]] std::optional<int> countOf(std::string_view word) const noexcept;

    // In-order traversal (lex order) -> flat list for next stage
    void inorderCollect(std::vector<std::pair<std::string,int>>& out) const;

    // ---------------------------- Metrics ----------------------
    [[nodiscard]] std::size_t size()   const noexcept;  // distinct words
    [[nodiscard]] unsigned    height() const noexcept;  // empty tree = 0

private:
    // ----------------------------- Data ------------------------
    TreeNode* root_ = nullptr;

    // --------------------------- Helpers -----------------------
    static void      destroy(TreeNode* node) noexcept;

    static TreeNode* insertHelper(TreeNode* node, const std::string& word);
    static TreeNode*       findNode(TreeNode* node, std::string_view word) noexcept;     // non-const for bulkInsert
    static const TreeNode* findNode(const TreeNode* node, std::string_view word) noexcept;

    static void inorderHelper(const TreeNode* node,
                              std::vector<std::pair<std::string,int>>& out);

    static std::size_t sizeHelper(const TreeNode* node)   noexcept;
    static unsigned    heightHelper(const TreeNode* node) noexcept;
};

#endif // IMPLEMENTATION_BINSEARCHTREE_H
