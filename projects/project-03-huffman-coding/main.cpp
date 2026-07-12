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

// Helper function to compare word frequency
bool compareByFrequency(const std::pair<std::string,int>& a,
                        const std::pair<std::string,int>& b)
{
    // Compare the counts in descending order
    if (a.second > b.second)
        return true;   // a should come before b

    if (a.second < b.second)
        return false;  // a should come after b

    // If counts are equal, compare the words in ascending order
    return a.first < b.first;   // "EX: apple comes before banana
}

int huffmanHeight(const HuffmanTree& ht) {
    std::vector<std::pair<std::string,std::string>> wcodes;
    ht.assignCodes(wcodes);

    if (wcodes.empty())
        return -1;
    if (wcodes.size() == 1)
        return 0;

    int maxLen = 0;
    for (size_t i = 0; i < wcodes.size(); ++i) {
        int len = wcodes[i].second.length();
        if (len > maxLen) {
            maxLen = len;
        }
    }
    return maxLen;
}

int sumLetters(const std::vector<std::string>& tokens) {
    int sum = 0;
    for (const auto& token : tokens) {
        sum += (int)token.size();
    }
    return sum;
}

int main(int argc, char *argv[]) {

    // 1) parse/validate args; open input file; print clear error message and exit non-zero if needed
    // Make sure user ran with only 1 filename
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    const std::string dirName = std::string("input_output");
    const std::string inputFileName = std::string(argv[1]);
    const std::string inputFileBaseName = baseNameWithoutTxt(inputFileName);


    // build the path to two file names: .tokens output file.
    const std::string fullInputPath      = dirName + "/" + inputFileName;
    const std::string wordTokensFileName = dirName + "/" + inputFileBaseName + ".tokens";
    const std::string freqFileName       = dirName + "/" + inputFileBaseName + ".freq";
    const std::string headerFileName     = dirName + "/" + inputFileBaseName + ".hdr";
    const std::string codeFileName       = dirName + "/" + inputFileBaseName + ".code";

    // The next several if-statement make sure that the input file, the directory exist
    // and that the output file is writeable.
     if( error_type status; (status = regularFileExistsAndIsAvailable(fullInputPath)) != NO_ERROR )
        exitOnError(status, fullInputPath);


    if (error_type status; (status = directoryExists(dirName)) != NO_ERROR )
        exitOnError(status, dirName);


    if (error_type status; (status = canOpenForWriting(wordTokensFileName)) != NO_ERROR)
        exitOnError(status, wordTokensFileName);


    if (error_type status; (status = canOpenForWriting(freqFileName)) != NO_ERROR)
        exitOnError(status, freqFileName);

    if (error_type status; (status = canOpenForWriting(headerFileName)) != NO_ERROR)
        exitOnError(status, headerFileName);

    if (error_type status; (status = canOpenForWriting(codeFileName)) != NO_ERROR)
        exitOnError(status, codeFileName);


    // Turn the inputfile into a list of words
    // 2) Scanner: read file -> vector<string> tokens; also write .tokens
    std::vector<std::string> words;
    namespace fs = std::filesystem;
    fs::path tokensFilePath(wordTokensFileName);

    Scanner fileToWords(fullInputPath);

    // CHANGE: one call that fills `words and writes the .tokens file with Scanner class
    if (error_type status; (status = fileToWords.tokenize(words, tokensFilePath)) != NO_ERROR) {
        // tokenize() returns errors
        exitOnError(status, wordTokensFileName);
    }


    // 3) BST: insert tokens -> build tree; obtain vector<pair<string,size_t>> frequencies (lexicographically by word)
    BinSearchTree bst;
    bst.bulkInsert(words);

    std::vector<std::pair<std::string,int>> wcPairs;  // (word, count) in word-lex order
    bst.inorderCollect(wcPairs);


    // 4) Print BST measures to stdout (exact labels/order)
    // H = BST Height
    // U is the number of distinct words
    // T is the size of the original token vector
    // MIN/MAX are taken over the frequencies
    // If the tree is empty, define height as 0 and set U, T, MIN, MAX to 0
    unsigned H;
    std::size_t U;
    std::size_t T;
    bool empty = words.empty();

    if (empty) {
        H = 0;          // height
        U = 0;          // unique words
        T = 0;          // total tokens
    } else {
        H = bst.height();
        U = bst.size();
        T = words.size();
    }

    int minFreq = 0;
    int maxFreq = 0;

    if (!empty && !wcPairs.empty()) {
        // Start with the first word's frequency as the initial min and max
        minFreq = wcPairs[0].second; // look at second element of wcPair
        maxFreq = wcPairs[0].second;

        // Loop through each word-count pair
        for (std::size_t i = 0; i < wcPairs.size(); i++) {
            int count = wcPairs[i].second;

            // Update min or max if needed
            if (count < minFreq) {
                minFreq = count;
            }
            if (count > maxFreq) {
                maxFreq = count;
            }
        }
    }

    if (empty) {
        // empty output required
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


    // 5) PriorityQueue: build from frequency vector; sort (count desc, word asc); write .freq
    // copy wcPairs to byFreq for sorting
    std::vector<std::pair<std::string,int>> byFreq = wcPairs;
    std::sort(byFreq.begin(), byFreq.end(), compareByFrequency);


    // 6) return 0 on success; non-zero on failure
    // write .freq files (count, word)
    std::ofstream out(freqFileName);
    if (!out.is_open()) {
        exitOnError(UNABLE_TO_OPEN_FILE_FOR_WRITING, freqFileName);
    }

    for (std::size_t i = 0; i < byFreq.size(); i++) {
        const std::string& word = byFreq[i].first;
        int count = byFreq[i].second;
        out << std::setw(10) << count << ' ' << word << '\n';

        // If a write fails
        if (!out) {
            exitOnError(FAILED_TO_WRITE_FILE, freqFileName);
        }
    }

    // Lexicographic order is preferred: "and", "at", "the"
    // test vector
    // std::vector<std::pair<std::string,int>> testWCPairs {
    //         {"and", 3},
    //         {"at",  2},
    //         {"the", 4}
    // };

    // Build the Huffman tree from sorted vector with word,count pairs
    HuffmanTree ht = HuffmanTree::buildFromCounts(wcPairs);

    // Print out HuffmanTree Metrics
    std::cout << "Huffman height: " << huffmanHeight(ht) << "\n";
    std::cout << "Sum of letters: " << sumLetters(words) << "\n";

    // Collect (word, code) results here
    std::vector<std::pair<std::string,std::string>> codes;
    ht.assignCodes(codes);

    std::ofstream hdrOut(headerFileName);
    if (!hdrOut.is_open()) {
        exitOnError(UNABLE_TO_OPEN_FILE_FOR_WRITING, headerFileName);
    }
    if (error_type status = ht.writeHeader(hdrOut); status != NO_ERROR)
        exitOnError(status, headerFileName);
    if (!hdrOut)
        exitOnError(FAILED_TO_WRITE_FILE, headerFileName);


    std::ofstream codeOut(codeFileName);
    if (!codeOut.is_open()) {
        exitOnError(UNABLE_TO_OPEN_FILE_FOR_WRITING, codeFileName);
    }
    if (error_type status = ht.encode(words, codeOut, 80); status != NO_ERROR)
        exitOnError(status, codeFileName);
    if (!codeOut)
        exitOnError(FAILED_TO_WRITE_FILE, codeFileName);

    // Test print for debugging the codebook
    // for (const auto& [word, code] : codes) {
    //     std::cout << word << ' ' << code << '\n';
    // }

    return 0;
}