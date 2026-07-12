# CS 315 Archive Rename Manifest

This manifest records the first, non-destructive organization pass for the
CS 315 Data Structures coursework archive. Paths use lowercase kebab-case,
retain official assignment numbers where known, and describe the subject of
the work rather than its completion state.

## Labs

| Original path | Organized path | Basis |
| --- | --- | --- |
| `Labs/dictionary-benchmark` | `labs/lab-01-adt-benchmark` | Lab 01: Abstract Data Types benchmark |
| `Labs/recursivePracticeProblems` | `labs/lab-03-mazes-and-recursion` | Lab 03: Solving Mazes and Recursion |
| `Labs/recursiveListProblems` | `labs/lab-04-recursive-list-problems` | Lab 04: Recursive-list-based problems |
| `Labs/recursiveListProblemsLab05` | `labs/lab-05-more-recursive-list-problems` | Lab 05: More recursive-list-based problems |
| `Labs/BinSearchTreeStudentFiles` | `labs/lab-06-binary-search-tree` | Lab 06: Binary-Search Tree |
| `Labs/HeapOrderedVectorBasedPQ` | `labs/lab-08-heap-priority-queue` | Lab 08: Heap-ordered complete-tree priority queue |
| `Labs/HashTablesOpenAddressingStudentFiles` | `labs/supplemental-open-addressing-hash-tables` | November hash-table work not numbered in the supplied syllabus; related to Project 5 Part 2 |

No corresponding working directory was located for Lab 02 (Data and Algorithm
Analysis), Lab 07 (Building a Huffman Tree), or Lab 09 (AVL Trees). Empty
directories were not created for them.

## Projects

| Original path | Organized path | Basis |
| --- | --- | --- |
| `Projects/Completed_Projects/CS315_Will_Meyer_Solving_A_Maze_Project` | `projects/project-01-maze-solver` | Project 1: Solving a maze |
| `Projects/Completed_Projects/Project_02_reclists_Will_Meyer` | `projects/project-02-recursive-lists` | Project 2: Recursive Lists |
| `Projects/Completed_Projects/Project_03_Meyer` | `projects/project-03-huffman-coding` | Canonical final Project 3 implementation |
| `Projects/Completed_Projects/Project_04_Meyer` | `projects/project-04-huffman-decoder` | Project 4: Decoding a Huffman-coded message |
| `Projects/Completed_Projects/priority-queue-study` | `projects/project-05-part-1-priority-queue-study` | Project 5 Part 1 |
| `Projects/project_05_part_2` | `projects/project-05-part-2-hash-table-analysis` | Project 5 Part 2, identified by its repository history and README |

## Practice and Later Revisions

| Original path | Organized path | Basis |
| --- | --- | --- |
| `data_structures_practice` | `practice/data-structures-practice` | Incomplete, post-course review work |
| `Projects/Class_TreeNode` | `practice/class-tree-node` | General BST/tree-node exercises; content does not implement a Huffman tree |
| `Projects/ChatGPT Re_Edits/Project_03_Meyer_GPT_Edit` | `practice/revisions/project-03-post-course-rework` | Post-submission Project 3 revision |

## Removed Redundant Archives

After the rename pass, the following collections were removed because they
duplicated the canonical project directories and included additional archived
copies of Git repositories:

- `projects/Completed_Projects_Submissions`
- `projects/Zipped_Projects`
- `labs/Zipped_Labs`

The canonical project directories under `projects/project-*` and the completed
lab directories under `labs/lab-*` were retained. The lab ZIPs were identified
as instructor-provided starter snapshots rather than canonical student work.

## Preserved for Later Review

The following artifact collections were deliberately not reorganized yet:

- `projects/HashMapAnalysis_StudentFiles`
- `projects/HashMapAnalysis_StudentFiles_Initial_Histogram`
- `projects/lru_profile.csv`

They contain submissions, starter/intermediate material, or large experimental
data that needs a separate deduplication and archive-storage decision.

During the initial rename pass, all nested `.git` directories, remotes, commit
histories, working-tree changes, build products, IDE metadata, and source files
were retained exactly as found. The later removal of redundant project archives
also removed the nested repository copy formerly stored at
`projects/Completed_Projects_Submissions/project_03_part1/.git`.

The remaining nested repositories were subsequently disconnected in preparation
for a single aggregate repository. Their former remotes, HEAD commits, and
working-tree states are recorded in `docs/git-consolidation-manifest.md`.

## Aggregate Repository Cleanup

Before initializing the aggregate repository, generated CMake build trees,
compiled binaries, IDE metadata, `.DS_Store` files, and empty legacy containers
were removed. Multi-gigabyte Project 5 trace and corpus inputs were retained
locally but excluded from Git, along with two pre-canonical Project 5 Part 2
working directories. Source code, reports, result CSVs, charts, and canonical
project directories were retained.
