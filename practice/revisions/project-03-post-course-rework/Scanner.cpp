// ===============================================================
// File:    Scanner.cpp
// Project: Project_03_Meyer_GPT_Edit
// Author:  Will Meyer
// Date:    2025-11-09
// Purpose: Implement tokenizer for phase 1.
//          Tokens are [a–z]+ or [a–z]+'[a–z]+ (apostrophe only internal).
//          Output variant writes one token per line, file ends with '\n'.
// ===============================================================

#include "Scanner.hpp"

// ---------------------------------------------------------------
// Section 1: Includes
// ---------------------------------------------------------------
#include <cctype>
#include <fstream>
#include <string>
#include <utility>
#include <vector>

#include "utils.hpp"

// ---------------------------------------------------------------
// Section 2: Construction
// ---------------------------------------------------------------
Scanner::Scanner(std::filesystem::path inputPath)
    : inputPath_(std::move(inputPath)) {}

// ---------------------------------------------------------------
// Section 3: Tokenization (in-memory)
// ---------------------------------------------------------------
error_type Scanner::tokenize(std::vector<std::string>& words) {
    std::ifstream in(inputPath_);
    if (!in) {
        return UNABLE_TO_OPEN_FILE;
    }

    words.clear();

    for (;;) {
        std::string word = readWord(in);
        if (word.empty()) break;
        words.push_back(std::move(word));
    }

    return NO_ERROR;
}

// ---------------------------------------------------------------
// Section 4: Tokenization (to file)
// ---------------------------------------------------------------
error_type Scanner::tokenize(std::vector<std::string>& words,
                             const std::filesystem::path& outputFile) {
    // First fill memory using the primary implementation
    if (error_type status = tokenize(words); status != NO_ERROR) {
        return status;
    }

    std::ofstream out(outputFile);
    if (!out.is_open()) {
        return UNABLE_TO_OPEN_FILE_FOR_WRITING;
    }

    // Write one token per line (always end with newline overall)
    for (const auto& w : words) {
        out << w << '\n';
        if (!out) return FAILED_TO_WRITE_FILE;
    }
    if (words.empty()) {
        out << '\n';
        if (!out) return FAILED_TO_WRITE_FILE;
    }

    return NO_ERROR;
}

// ---------------------------------------------------------------
// Section 5: Helpers
// ---------------------------------------------------------------
std::string Scanner::readWord(std::istream& in) {
    // Find the first letter (skip separators)
    std::string token;
    char c;

    // Skip until we hit a letter or EOF
    while (in.get(c)) {
        if (std::isalpha(static_cast<unsigned char>(c))) {
            token.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(c))));
            break;
        }
    }

    // If we never started a token, return ""
    if (token.empty()) {
        return "";
    }

    // Grow token: accept letters; accept apostrophe only if followed by a letter
    while (in.get(c)) {
        if (std::isalpha(static_cast<unsigned char>(c))) {
            token.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(c))));
            continue;
        }

        if (c == '\'') {
            const int look = in.peek();
            if (look != std::char_traits<char>::eof()) {
                const char d = static_cast<char>(look);
                if (std::isalpha(static_cast<unsigned char>(d))) {
                    // consume apostrophe and next letter
                    token.push_back('\'');
                    in.get(c);
                    token.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(c))));
                    continue;
                }
            }
            // Apostrophe not followed by a letter -> stop the token (apostrophe excluded)
            return token;
        }

        // Any other separator ends the token
        break;
    }

    return token;
}
