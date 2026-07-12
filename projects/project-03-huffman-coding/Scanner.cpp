//
// Created by Ali Kooshesh on 9/27/25.
//
// Scanner.cpp
// Implement tokenizer for phase 1 of project_03
// Tokens are [a–z]+ or [a–z]+'[a–z]+ (apostrophe only between letters).
// Output: one token per line and file ends with a newline.


#include <utility>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include "Scanner.hpp"
#include "utils.hpp"

Scanner::Scanner(std::filesystem::path inputPath) {
    // You complete this...
    // Store the input file path (the .txt path to scan)
    inputPath_ = inputPath;

}


error_type Scanner::tokenize(std::vector<std::string>& words) {
    // opens the input, loops on readWord, fills words, returns NO_ERROR
    // Tokenize into memory (according to the Rules in this section).

    // open the input file (inputPath_)
    std::ifstream in(inputPath_);
    // if it fails, return UNABLE_TO_OPEN_FILE.
    if (!in) {
        return UNABLE_TO_OPEN_FILE;
    }
    // clear words to guarantee empty vector
    words.clear();
    std::string word = readWord(in);
    // repeatedly call readWord(in) until it returns "".
    while (!word.empty()) {
        words.push_back(word);  // push each non-empty token into words.
        word = readWord(in);
    }
    return NO_ERROR;  // return NO_ERROR on success
}


// This overload reimplements output writing directly rather than using writeVectorToFile
error_type Scanner::tokenize(std::vector<std::string>& words,
                        const std::filesystem::path& outputFile) {
    // calls the in-memory version, then writes one token per line and a final newline,
    // with correct error codes on failure.

    // Call the in-memory tokenizer to fill words.
    // If it fails, return error
    error_type status = tokenize(words);
    if (status != NO_ERROR) {
        return status;
    }


    // Open the output file for writing
    // If open fails, return UNABLE_TO_OPEN_FILE_FOR_WRITING.
    std::ofstream out(outputFile);
    if (!out.is_open()) {
        return UNABLE_TO_OPEN_FILE_FOR_WRITING;
    }

    // write each token to its own line (range based loop)
    // if any write fails, return FAILED_TO_WRITE_FILE.
    for (const auto& word : words) {
        out << word << '\n';
        if (!out) {
            return FAILED_TO_WRITE_FILE;
        }
    }

    // If words is empty, still write a newline.
    if (words.empty()) {
        out << '\n';
        if (!out) {
            return FAILED_TO_WRITE_FILE;
        }
    }
    // Return NO_ERROR on success.
    return NO_ERROR;
}


std::string Scanner::readWord(std::istream& in) {
    // follows the exact rules (ASCII letters; valid internal '; separators everywhere else).
    // Read the next token from 'in'. Returns empty string when no more tokens.
    // Follows the project’s tokenization rules: letters a–z with optional internal apostrophes;
    // digits, punctuation, hyphens/dashes, whitespace, and non-ASCII are separators.
    // Converts uppercase to lowercase letters.
    // Returns "" when the stream has no more tokens.

    // Find where word starts and skip separators until we hit a letter
    // then start a lowercase token.
    std::string token;
    char c;
    while (in.get(c)) {
        if (std::isalpha(static_cast<unsigned char>(c))) {
            c = std::tolower(static_cast<unsigned char>(c));
            token.push_back(c);
            break;
        }
    }
    // if we didn't find a letter and done reading in, return "".
    if (token.empty() && !in) {
        return "";
    }
    // Build the tokens by adding letters to complete words
    // Only allow apostrophes if the next character is a letter.
    while (in.get(c)) {
        if (std::isalpha(static_cast<unsigned char>(c))){
            c = std::tolower(static_cast<unsigned char>(c));
            token.push_back(c);
        }
        // If the next character is a letter, push both the apostrophe and the letter.
        // Otherwise, return the completed token without the apostrophe
        else if (c == '\'') {
            int lookahead = in.peek();
            if (lookahead != EOF){
                char d = static_cast<char>(lookahead);
                if (std::isalpha(static_cast<unsigned char>(d))) {
                    token.push_back('\'');
                    in.get(c);
                    c = std::tolower(static_cast<unsigned char>(c));
                    token.push_back(c);
                    continue;
                }
            }
                return token;
        }
        else {
            break;
        }
    }
    // Return the completed token
    return token;
}

