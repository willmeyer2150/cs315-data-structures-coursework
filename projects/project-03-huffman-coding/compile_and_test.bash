#!/bin/bash

# Check for exactly one argument
if [ "$#" -ne 1 ]; then
  echo "Usage: $0 <input_filename>"
  exit 1
fi
input_file_name_no_dir=$1
INPUT_FILE="input_output/$1"

# 1. Make sure the input file exists in input_output directory
if [ ! -f "$INPUT_FILE" ]; then
  echo "Error: File '$INPUT_FILE' does not exist."
  exit 1
fi

# 2. Compile the project
echo "Compiling project..."
g++ -std=c++20 -Wall *.cpp -o p3_part1.x
if [ $? -ne 0 ]; then
  echo "Compilation failed."
  exit 1
fi

# 3. Run the program using the input file
echo "Running program with input file '$INPUT_FILE'..."
./p3_part1.x "$INPUT_FILE"
if [ $? -ne 0 ]; then
  echo "Program exited with a non-zero status. Terminating...."
  exit 1
fi

TOKEN_FILE=$(echo $input_file_name_no_dir | sed 's/.txt$/.tokens/')

tokens_dir="/home/faculty/kooshesh/cs315_f2025_p3_part1/part1_tokens_files/"
echo diff input_output/$TOKEN_FILE  $tokens_dir/$TOKEN_FILE
diff input_output/$TOKEN_FILE  $tokens_dir/$TOKEN_FILE



