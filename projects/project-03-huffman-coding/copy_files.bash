#!/bin/bash


src="/home/faculty/kooshesh/cs315_f2025_p3_part1/part1_data_files/"
dst="./input_output"

# Check if source directory exists
if [ ! -d "$src" ]; then
  echo "Error: Source directory '$src' does not exist."
  exit 1
fi

# Check if destination directory exists
if [ ! -d "$dst" ]; then
  echo "Error: Destination directory '$dst' does not exist."
  exit 1
fi

# Copy files from source to destination
# -a preserves attributes, -v is verbose
cp -av "$src"/* "$dst"/

echo "Files copied from '$src' to '$dst'."
