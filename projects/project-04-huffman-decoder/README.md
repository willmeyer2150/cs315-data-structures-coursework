## Project 04 — Huffman Decoder (CS 315)

**Student Information**
Name: Will Meyer   

___

## Collaboration & Sources

This project is my own work. I used the following resources to get through parts that I didn't understand or to learn new coding techniques:

**Course materials:** 
- Project 03 `TreeNode.hpp` & `Utils.hpp` copied over.

**C++ references:** 
- cppreference.com for <fstream>, <string>, streams, and error handling ideas.

**AI tools (ChatGPT):**
- Used for brainstorming edge cases, organizing testing and debugging, and refining this README. 
- I wrote the code myself and AI suggestions were adapted into comments and for verification of my ideas.
  - (Example of Help Needed: input validation, path decoding error debugs, recognizing single-leaf edge case handling
as well as other edge cases).

I modified any code found online to match the project brief and my code style.

---

## Implementation Details

**Overview**

This program reconstructs a Huffman tree from a header file (.hdr) and decodes a bitstream file (.code) back into tokens. Output is written to input_output/<basename>.tokens_decoded, one token per line.

**File & Directory I/O**

- All I/O found in input_output/.

**Program execution:**

- ./Project_04_Meyer <header-file.hdr> <code-file.code>

**Example:**

- ./Project_04_Meyer TheBells.hdr TheBells.code

**Output file name:** 
- <basename(header)>.tokens_decoded.

**Data Structures**
- HuffmanTree with a TreeNode class storing:
  - a token, or word (std::string) for leaf nodes 
  - left & right child pointers for internal nodes 
- Root is created empty and populated by traversing the code paths from the header pairs.

**Header Parsing (readHeader() function)**
- Reads input_output/<hdr> line-by-line. 
- Each non-empty line is split at the last space:
  - token = line.substr(0, last_space)
  - code = line.substr(last_space + 1) (must be only 0/1)
- Removes trailing spaces on token.
- Validation and Error Reporting:
  - Missing space → HDR_PARSE_ERROR 
  - Empty code or non-binary characters → HDR_BAD_CODE_BITS 
  - Empty file → HDR_EMPTY
- Returns NO_ERROR on success and fills std::vector<std::pair<std::string,std::string>> header_pairs.

**Tree Construction (HuffmanTree::buildFromHeader() function)**
- Destroys any existing tree. 
- Starts with an empty-token root. 
- For each (token, code):
  - Traverses the tree using 0 → left, 1 → right. 
  - Creates internal nodes as needed (empty tokens). 
  - After consuming the code bits, sets the leaf’s token (word).
- Input validation:
  - Bad bit → HDR_BAD_CODE_BITS 
  - Null traversal (shouldn't happen since readheader() was successful) → HDR_PARSE_ERROR 
  - Empty header → HDR_EMPTY

**Decoding (HuffmanTree::decode)**
- Streams characters from the .code file:
  - Skips whitespace (' ', '\n', '\r'). 
  - Accepts only 0 or 1, otherwise HDR_BAD_CODE_BITS.
- If only 1 node (root is a leaf): write the root token for every valid bit read.
- Expected case:
  - Traverse left/right for each bit. 
  - On reaching a leaf, write token to output and reset to root. 
  - If traversal hits nullptr → HDR_PARSE_ERROR. 
- At EOF:
  - If we’re at middle of path (not back at root in a branched tree) → HDR_PARSE_ERROR.
- Returns NO_ERROR on success.

**Error Handling**
- Centralized error_type enum and helpers in utils.hpp:
  - NO_ERROR, UNABLE_TO_OPEN_FILE, HDR_PARSE_ERROR, HDR_BAD_CODE_BITS, HDR_EMPTY, etc.
- Guard rails in main():
  - Checks directory, file existence, and writability. 
  - Exits via exitOnError(...) with descriptive messaging.

**Memory Management**
- HuffmanTree::destroy recursively deletes all nodes (post-order traversal) to prevent leaks.
- Tree is rebuilt from scratch for each run.

---

## Testing & Status

**What Works**
- Validates and parses .hdr with tokens that may include spaces. 
- Rejects bad lines, non-binary codes, and empty headers. 
- Builds the Huffman tree deterministically from (token, code) pairs. 
- Decodes .code streams (requires only 0/1). 
- Handles single node Huffman trees. 
- Detects incomplete trailing code paths at EOF. 
- Writes tokens one per line to <basename>.tokens_decoded.

**How to Build**

Example with g++:

```
g++ -std=c++17 -O2 -Wall \
    main.cpp HuffmanTree.cpp utils.cpp TreeNode.cpp \
    -o Project_04_Meyer
```
- -Wall enables common warnings

**How to Run**

1. Test files in input_output
2. Run:
```
./Project_04_Meyer TheBells.hdr TheBells.code
```

**Test Cases I Used**
1. Good path
- A known good `.hdr/.code` pair from Project 03 output.
2. Header Errors
- Line with no space -> `HDR_PARSE_ERROR`
- Code with `2` or `a` -> `HDR_BAD_CODE_BITS`
- Empty file -> `HDR_EMPTY`
3. Decode Errors
- `.code` includes `2` or letters -> `HDR_BAD_CODE_BITS`
- Code ends mid symbol (incomplete path) -> `HDR_PARSE_ERROR`
4. Single Node Tree
- Header contains one token mapped to an empty path's leaf via a one bit code
  - All input bits should emit the same token.
5. Whitespace Handling
- `.code` with spaces/newlines mixed in -> still decodes correctly

**NOTE** : I temporarilily enabled the tree printer in main() to visually test `buildFromHeader()`.

## Summary

This project has been a big step forward in my undestanding of file I/O in C++. Implementing and debugging
this decoder helped me to develop a much stronger understanding of input and output streams.

I also feel that I leveled up my ability with `std::vector` containers that store `std::pair
types. 

Another area I grew with this project was my ability to understand string parsing, particularly with whitespace. It
helped me to systematically work through edge cases and handle unexpected characters using c++ library functionality.

Overall, the decoder meets the brief expectations for input validation, tree construction and complete decoding of the 
bitstream and printed text to the output stream. My code returns appropriate errors if need be, and when run on blue, 
I get no differences from the test script files. (See blue_output.txt for successful run details).
