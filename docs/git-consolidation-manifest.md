# Git Consolidation Manifest

This document records the nested repositories that existed before the CS 315
coursework was consolidated into one repository. The nested `.git` directories
were removed after recording this information; the working files, including
uncommitted changes, were retained.

## Repository Heads

| Former repository path | Former origin | Branch | Last commit |
| --- | --- | --- | --- |
| `labs/lab-01-adt-benchmark` | `https://github.com/SSU-CS315-Fall2025-Lab01/Lab01_ADTs.git` | `main` | `776671f4784bb65dbe9ac1f4d0eeb10ab3870f12` — Implemented updates for Lab01 -- Insert and Lookup functions for SortedLinkedListDict (2025-08-24) |
| `projects/project-01-maze-solver` | `git@github.com:willmeyer2150/CS315_Will_Meyer_Solving_A_Maze_Project.git` | `main` | `a408ccba48257a70f8a985c0d776d0d6dfccdb37` — Final submission: argv[] support + cleanup (2025-09-14) |
| `projects/project-02-recursive-lists` | `git@github.com:willmeyer2150/Project_02_reclists_Will_Meyer.git` | `main` | `59820d3405cbc03ed03660da646e4c44bb9d3be6` — Final README.md edit to reflect changes (2025-10-07) |
| `projects/project-03-huffman-coding` | `git@github.com:willmeyer2150/Project_03_Meyer.git` | `main` | `37dc902d5b7cf1fda96e4e27d9a60e1804719ebc` — feat: updated final_output.txt file with successful output from blue with new metrics (2025-10-24) |
| `projects/project-04-huffman-decoder` | `git@github.com:willmeyer2150/Project_04_Meyer` | `main` | `41ee19a6f4ee213cc34c865c80bd33be97e60ba2` — adjust Readme (2025-11-05) |
| `projects/project-05-part-1-priority-queue-study` | `git@github.com:willmeyer2150/Project_05_Meyer.git` | `main` | `cd56f414f3a757ec02f3fbf855c01ea246b52e85` — feat final commit (2025-11-14) |
| `projects/project-05-part-2-hash-table-analysis` | `git@github.com:willmeyer2150/project_05_part_2.git` | `main` | `1a8d53486bb71fd1ad461f8462c9614c07e3edba` — update readme (2025-12-04) |
| `practice/revisions/project-03-post-course-rework` | `git@github.com:willmeyer2150/Project_03_Meyer.git` | `main` | `37dc902d5b7cf1fda96e4e27d9a60e1804719ebc` — feat: updated final_output.txt file with successful output from blue with new metrics (2025-10-24) |

## Working Changes Retained During Consolidation

The following files differed from their former repository heads when the nested
repositories were disconnected.

### Lab 01

- Modified: `Dictionary.hpp`, `README.md`, `SortedLinkedListDict.cpp`,
  `SortedLinkedListDict.hpp`, `SortedVectorDict.cpp`, `SortedVectorDict.hpp`,
  `UnsortedLinkedListDict.cpp`, `UnsortedLinkedListDict.hpp`,
  `UnsortedVectorDict.hpp`, `main.cpp`

### Project 02

- Modified: `main.cpp`, `solutions.cpp`
- Untracked: `blue_confirmation.txt`

### Project 04

- Modified: `main.cpp`

### Project 05 Part 1

- Modified: `.DS_Store`, `.idea/editor.xml`, `.idea/priority-queue-study.iml`
- Untracked: `.idea/deployment.xml`, `src/.DS_Store`,
  `src/implementations/.DS_Store`, `src/trace-generators/.DS_Store`,
  `traces/.DS_Store`

### Project 05 Part 2

- Modified: `csvs/lru_profile.csv`

### Project 03 Post-Course Rework

- Modified: `BinSearchTree.cpp`, `BinSearchTree.hpp`, `HuffmanTree.cpp`,
  `HuffmanTree.hpp`, `PriorityQueue.cpp`, `PriorityQueue.hpp`, `Scanner.cpp`,
  `Scanner.hpp`, `TreeNode.hpp`, `main.cpp`, `utils.cpp`, `utils.hpp`

Projects 01 and 03 had clean working trees at consolidation time.

## Scope

Removing a local `.git` directory disconnects that working directory and removes
its local history. It does not delete or modify the corresponding GitHub
repository. Remote deletion is a separate manual action.
