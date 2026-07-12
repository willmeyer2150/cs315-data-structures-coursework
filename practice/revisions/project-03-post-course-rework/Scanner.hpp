// ===============================================================
// File:    Scanner.hpp
// Project: Project_03_Meyer_GPT_Edit
// Author:  Will Meyer
// Date:    2025-11-09
// Purpose: File-to-token scanner.
//          - tokenize() -> vector<string>
//          - tokenize(..., outputPath) -> writes one token per line
//          Tokens: [a–z]+ or [a–z]+'[a–z]+ (apostrophe only internal).
// ===============================================================

#ifndef IMPLEMENTATION_FILETOWORDS_HPP
#define IMPLEMENTATION_FILETOWORDS_HPP

// ---------------------------------------------------------------
// Section: Includes
// ---------------------------------------------------------------
#include <string>
#include <vector>
#include <filesystem>
#include <iosfwd>     // std::istream forward decl

#include "utils.hpp"

// ---------------------------------------------------------------
// Section: Class Declaration
// ---------------------------------------------------------------
class Scanner {
public:
    explicit Scanner(std::filesystem::path inputPath);

    // Tokenize into memory (according to the project rules).
    error_type tokenize(std::vector<std::string>& words);

    // Tokenize and also write one token per line to 'outputFile'.
    // Internally calls the in-memory tokenize() to avoid duplicate logic.
    error_type tokenize(std::vector<std::string>& words,
                        const std::filesystem::path& outputFile);

    ~Scanner() = default;

private:
    // Read the next token from 'in'. Returns empty string when no more tokens.
    // Rules: ASCII letters with optional internal apostrophes; everything else
    // (digits, punctuation, hyphens/dashes, whitespace, non-ASCII) is a separator.
    // Converts uppercase to lowercase.
    static std::string readWord(std::istream& in);

    std::filesystem::path inputPath_;
};

#endif // IMPLEMENTATION_FILETOWORDS_HPP
