#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <utility>

#include "HuffmanTree.hpp"
#include "utils.hpp"

// Reads a header file and extracts word/code pairs
// Pre-condition: the header file should contain 1 header/code per line separated by a white space
// Post: returns error type if problems with file reading, or NO_ERROR

// Read the codebook (
error_type readHeader(const std::string& fullHdrInputPath,
    std::vector<std::pair<std::string, std::string>>& header_pairs) {

    // Try to open header file
    std::ifstream hdrFile(fullHdrInputPath);
    if (!hdrFile.is_open()) {
        return UNABLE_TO_OPEN_FILE;
    }

    // always clear existing data to start with a clean vector
    header_pairs.clear();

    std::string line;
        // reads the header file line by line
       while (std::getline(hdrFile, line)) {
           // skip empty lines
           if (line.empty())
               continue;

           // If no space is found, invalid -- throw error
           int last_space = -1;
           for (int i = static_cast<int>(line.size()) - 1; i >= 0; --i) {
               if (line[i] == ' ') {
                   last_space = i;
                   break;
               }
           }

           if (last_space == -1) {
               return HDR_PARSE_ERROR;
           }
            // Extracts the token and code from the line
           std::string token = line.substr(0, last_space);
           std::string code = line.substr(last_space + 1);

           // clean up any spaces around the token
           while (!token.empty() && token.back() == ' ')
               token.pop_back();

           // ensure code is not empty and is 0 or 1
           if (code.empty()) {
               return HDR_BAD_CODE_BITS;
           } else {
               for (char c : code) {
                   if (c != '0' && c != '1') {
                       return HDR_BAD_CODE_BITS;
                   }
               }
           }
            // store the validated pair in the vector
           header_pairs.emplace_back(token, code);

       }

       // Check for read errors and throw error if found
       if (hdrFile.fail() && !hdrFile.eof()) {
           return HDR_PARSE_ERROR;
       }
       // check for at least one read of a word/code
       if (header_pairs.empty()) {
           return HDR_EMPTY;
       }

       return NO_ERROR;
}

int main(int argc, char *argv[]) {

    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " filename1.hdr filename2.code\n";
        return 1;
    }

    const std::string dirName               = std::string("input_output");
    const std::string hdrInputFileName      = std::string(argv[1]);
    const std::string codeInputFileName     = std::string(argv[2]);
    const std::string OutputFileBaseName    = baseNameWithoutExt(hdrInputFileName);

    // Building the path to the file names:
    const std::string fullHdrInputPath      = dirName + "/" + hdrInputFileName;
    const std::string fullCodeInputPath     = dirName + "/" + codeInputFileName;
    const std::string tokensDecodedFileName = dirName + "/" + OutputFileBaseName + ".tokens_decoded";

    if ( error_type status; (status = directoryExists(dirName)) != NO_ERROR )
        exitOnError(status, dirName);

    if ( error_type status; (status = regularFileExistsAndIsAvailable(fullHdrInputPath)) != NO_ERROR )
        exitOnError(status, fullHdrInputPath);

    if ( error_type status; (status = regularFileExistsAndIsAvailable(fullCodeInputPath)) != NO_ERROR )
        exitOnError(status, fullCodeInputPath);

    if ( error_type status; (status = canOpenForWriting(tokensDecodedFileName)) != NO_ERROR )
        exitOnError(status, tokensDecodedFileName);

    std::vector<std::pair<std::string, std::string>> header_pairs;
    if ( error_type status; (status = readHeader(fullHdrInputPath, header_pairs)) != NO_ERROR )
        exitOnError(status, fullHdrInputPath);

    HuffmanTree ht;
    if (error_type status; (status = ht.buildFromHeader(header_pairs)) != NO_ERROR )
        exitOnError(status, fullHdrInputPath);

    // debug print buildFromHeader
    // std::cout << "\nHeader read successfully. Now printing tree:\n";
    // ht.printTree();

    std::ifstream codeFile(fullCodeInputPath);
    if (!codeFile.is_open()) {
        return UNABLE_TO_OPEN_FILE;
    }

    std::ofstream tokenFile(tokensDecodedFileName);
    if (!tokenFile) {
        return UNABLE_TO_OPEN_FILE;
    }

    if (error_type status; (status = ht.decode(codeFile, tokenFile)) != NO_ERROR )
        exitOnError(status, codeInputFileName);

    // Testing write to output file
    // std::cout << "Type a line to save:\n> ";
    // std::string line;
    // if (std::getline(std::cin, line)) {
    //     tokenFile << line << '\n';
    // }
    //
    // std::string line2 = "it works";
    // tokenFile << line2 << std::endl;

    return 0;
}