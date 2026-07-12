// ===============================================================
// File:    main.cpp
// Project: Project_03_Meyer_GPT_Edit
// Author:  Will Meyer
// Date:    2025-11-09
// Purpose: Orchestrates the Huffman pipeline:
//          1) parse args
//          2) tokenize input -> .tokens
//          3) build BST -> gather (word,count)
//          4) report BST metrics
//          5) sort by frequency -> write .freq
//          6) build Huffman tree
//          7) write .hdr and .code
// ===============================================================

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <utility>

#include "BinSearchTree.hpp"
#include "HuffmanTree.hpp"
#include "Scanner.hpp"
#include "utils.hpp"

// ---------------------------------------------------------------
// Section 1: Constants & Helper Functions
// ---------------------------------------------------------------
namespace {
    constexpr int DEFAULT_WRAP_COLS = 80;

    // Compare by frequency (desc), then word (asc)
    bool compareByFrequency(const std::pair<std::string,int>& a,
                            const std::pair<std::string,int>& b)
    {
        if (a.second != b.second) return a.second > b.second;  // desc by count
        return a.first < b.first;                               // asc by word
    }

    // Compute Huffman tree "height" as max code length (-1 empty, 0 one symbol)
    int huffmanHeight(const HuffmanTree& ht) {
        std::vector<std::pair<std::string,std::string>> wordCodePairs;
        ht.assignCodes(wordCodePairs);

        if (wordCodePairs.empty())  return -1;
        if (wordCodePairs.size() == 1) return 0;

        int maxLen = 0;
        for (const auto& kv : wordCodePairs) {
            const int len = static_cast<int>(kv.second.length());
            if (len > maxLen) maxLen = len;
        }
        return maxLen;
    }

    // Sum of token lengths (letters)
    int sumLetters(const std::vector<std::string>& tokens) {
        int sum = 0;
        for (const auto& token : tokens) sum += static_cast<int>(token.size());
        return sum;
    }
} // namespace

// ---------------------------------------------------------------
// Section 2: main()
// ---------------------------------------------------------------
int main(int argc, char *argv[]) {

    // ===== Stage 1: Parse & validate args ===================================
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    const std::string dirName           = "input_output";
    const std::string inputFileName     = std::string(argv[1]);
    const std::string inputFileBaseName = baseNameWithoutTxt(inputFileName);

    // Build canonical paths
    const std::string fullInputPath      = dirName + "/" + inputFileName;
    const std::string wordTokensFileName = dirName + "/" + inputFileBaseName + ".tokens";
    const std::string freqFileName       = dirName + "/" + inputFileBaseName + ".freq";
    const std::string headerFileName     = dirName + "/" + inputFileBaseName + ".hdr";
    const std::string codeFileName       = dirName + "/" + inputFileBaseName + ".code";

    // ===== Stage 2: Pre-flight I/O checks ===================================
    if (error_type status; (status = regularFileExistsAndIsAvailable(fullInputPath)) != NO_ERROR)
        exitOnError(status, fullInputPath);

    if (error_type status; (status = directoryExists(dirName)) != NO_ERROR)
        exitOnError(status, dirName);

    if (error_type status; (status = canOpenForWriting(wordTokensFileName)) != NO_ERROR)
        exitOnError(status, wordTokensFileName);

    if (error_type status; (status = canOpenForWriting(freqFileName)) != NO_ERROR)
        exitOnError(status, freqFileName);

    if (error_type status; (status = canOpenForWriting(headerFileName)) != NO_ERROR)
        exitOnError(status, headerFileName);

    if (error_type status; (status = canOpenForWriting(codeFileName)) != NO_ERROR)
        exitOnError(status, codeFileName);

    // ===== Stage 3: Tokenize input -> vector<string> + write .tokens =========
    std::vector<std::string> words;
    namespace fs = std::filesystem;
    fs::path tokensFilePath(wordTokensFileName);

    Scanner fileToWords(fullInputPath);
    if (error_type status; (status = fileToWords.tokenize(words, tokensFilePath)) != NO_ERROR) {
        exitOnError(status, wordTokensFileName);
    }

    // ===== Stage 4: Build BST & collect (word,count) in lex order ============
    BinSearchTree bst;
    bst.bulkInsert(words);

    std::vector<std::pair<std::string,int>> wordCountPairs;  // (word, count), lexicographic by word
    bst.inorderCollect(wordCountPairs);

    // ===== Stage 5: Compute & print BST metrics ==============================
    // H = BST height; U = unique words; T = total tokens; MIN/MAX over frequencies
    const bool empty = words.empty();

    unsigned    H = 0;
    std::size_t U = 0;
    std::size_t T = 0;

    if (!empty) {
        H = bst.height();
        U = bst.size();
        T = words.size();
    }

    int minFreq = 0, maxFreq = 0;
    if (!empty && !wordCountPairs.empty()) {
        minFreq = wordCountPairs.front().second;
        maxFreq = wordCountPairs.front().second;
        for (const auto& kv : wordCountPairs) {
            const int c = kv.second;
            if (c < minFreq) minFreq = c;
            if (c > maxFreq) maxFreq = c;
        }
    }

    if (empty) {
        std::cout << "BST height: 0\n"
                  << "BST unique words: 0\n"
                  << "Total tokens: 0\n"
                  << "Min frequency: 0\n"
                  << "Max frequency: 0\n";
    } else {
        std::cout << "BST height: " << H << "\n"
                  << "BST unique words: " << U << "\n"
                  << "Total tokens: " << T << "\n"
                  << "Min frequency: " << minFreq << "\n"
                  << "Max frequency: " << maxFreq << "\n";
    }

    // ===== Stage 6: Sort by frequency (desc, word asc) -> write .freq ========
    std::vector<std::pair<std::string,int>> byFreq = wordCountPairs;
    std::sort(byFreq.begin(), byFreq.end(), compareByFrequency);

    std::ofstream out(freqFileName);
    if (!out.is_open()) exitOnError(UNABLE_TO_OPEN_FILE_FOR_WRITING, freqFileName);

    for (const auto& [word, count] : byFreq) {
        out << std::setw(10) << count << ' ' << word << '\n';
        if (!out) exitOnError(FAILED_TO_WRITE_FILE, freqFileName);
    }

    // ===== Stage 7: Build Huffman tree, report metrics, write .hdr/.code =====
    HuffmanTree ht = HuffmanTree::buildFromCounts(wordCountPairs);

    std::cout << "Huffman height: " << huffmanHeight(ht) << "\n";
    std::cout << "Sum of letters: " << sumLetters(words) << "\n";

    // (Optional) collect codes for debug
    std::vector<std::pair<std::string,std::string>> wordCodePairs;
    ht.assignCodes(wordCodePairs);

    // .hdr
    std::ofstream hdrOut(headerFileName);
    if (!hdrOut.is_open()) exitOnError(UNABLE_TO_OPEN_FILE_FOR_WRITING, headerFileName);

    if (error_type status = ht.writeHeader(hdrOut); status != NO_ERROR)
        exitOnError(status, headerFileName);
    if (!hdrOut) exitOnError(FAILED_TO_WRITE_FILE, headerFileName);

    // .code
    std::ofstream codeOut(codeFileName);
    if (!codeOut.is_open()) exitOnError(UNABLE_TO_OPEN_FILE_FOR_WRITING, codeFileName);

    if (error_type status = ht.encode(words, codeOut, DEFAULT_WRAP_COLS); status != NO_ERROR)
        exitOnError(status, codeFileName);
    if (!codeOut) exitOnError(FAILED_TO_WRITE_FILE, codeFileName);

    // Debug dump example:
    // for (const auto& [w,c] : wordCodePairs) std::cout << w << ' ' << c << '\n';

    return 0;
}
