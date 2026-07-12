# CS 315: Data Structures Archive

This repository collects my work from CS 315, Data Structures, at Sonoma State
University during Fall 2025. It consolidates coursework that was originally
spread across several repositories into a single chronological archive.

The archive includes small lab exercises, larger programming projects, and a
separate area for incomplete post-course practice. Assignment implementations
are preserved substantially as they existed at the end of the course; the
top-level organization and documentation were added later for clarity.

## Projects

| Assignment | Topic | Directory |
| --- | --- | --- |
| Project 1 | Maze solving with stacks and recursion | [`project-01-maze-solver`](projects/project-01-maze-solver) |
| Project 2 | Recursive list operations | [`project-02-recursive-lists`](projects/project-02-recursive-lists) |
| Project 3 | Huffman trees and encoding | [`project-03-huffman-coding`](projects/project-03-huffman-coding) |
| Project 4 | Decoding Huffman-coded messages | [`project-04-huffman-decoder`](projects/project-04-huffman-decoder) |
| Project 5, Part 1 | Experimental priority-queue analysis | [`project-05-part-1-priority-queue-study`](projects/project-05-part-1-priority-queue-study) |
| Project 5, Part 2 | Open-addressing hash-table analysis | [`project-05-part-2-hash-table-analysis`](projects/project-05-part-2-hash-table-analysis) |

## Labs

| Assignment | Topic | Directory |
| --- | --- | --- |
| Lab 1 | Abstract data types and benchmarking | [`lab-01-adt-benchmark`](labs/lab-01-adt-benchmark) |
| Lab 3 | Mazes and recursion | [`lab-03-mazes-and-recursion`](labs/lab-03-mazes-and-recursion) |
| Lab 4 | Recursive-list problems | [`lab-04-recursive-list-problems`](labs/lab-04-recursive-list-problems) |
| Lab 5 | Additional recursive-list problems | [`lab-05-more-recursive-list-problems`](labs/lab-05-more-recursive-list-problems) |
| Lab 6 | Binary-search trees | [`lab-06-binary-search-tree`](labs/lab-06-binary-search-tree) |
| Lab 8 | Heap-ordered priority queues | [`lab-08-heap-priority-queue`](labs/lab-08-heap-priority-queue) |
| Supplemental | Open-addressing hash tables | [`supplemental-open-addressing-hash-tables`](labs/supplemental-open-addressing-hash-tables) |

No corresponding working directories were located for Labs 2, 7, or 9 when
the archive was assembled.

## Practice

[`practice/data-structures-practice`](practice/data-structures-practice) is an
incomplete attempt to revisit course concepts after the class. The
[`practice/revisions`](practice/revisions) directory contains later experimental
revisions and is not presented as submitted coursework.

## Large Experimental Data

Project 5 generated several gigabytes of reproducible trace and corpus files.
Those local datasets are excluded from Git; the generators, implementations,
result CSVs, reports, and charts are retained in the repository.

## Archive Notes

- [`docs/rename-manifest.md`](docs/rename-manifest.md) records the directory
  reorganization and discarded redundant archives.
- [`docs/git-consolidation-manifest.md`](docs/git-consolidation-manifest.md)
  records the former repositories and their last known commits before local Git
  metadata was removed.
