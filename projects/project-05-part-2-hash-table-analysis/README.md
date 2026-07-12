## 1. Student Information

**Name:** Will Meyer  

---

## 2. Collaboration & Sources

**This project is my own work as stipulated below:**

- I built the hash table harness by refactoring code from the Huffman Project, taking what I needed from the hash table stand alone application.
- I emitted the proper CSV file as well as the 0/1 occupancy map to import into the D3 plotting and histogram applications in order to study metrics for analysis.
- I analyzed the data and wrote the paper as well as preparing the content in this README.md file.

#### **The following sources were used to overcome roadblocks**

- Discussion with classmates around implementation details
- Questions to the professor

**AI (_mostly ChatGPT_) was used for the following**

- Substantial help was needed to implement the trace generator. I was unable to put the pieces together due increased complexity over previous projects. ChatGPT was somewhat helpful by providing a solution that would compile and emit traces. I still had to confirm their validity.
- ChatGPT was also used in parts of my analysis for clarifications on expected behavior of a hash table. I used its input for minimal sanitization, but my goal was to maintain my voice. I did like some of the formatting suggestions it gave, like using bold or italics type to emphasize points. I have been adopting these practices as I have seen its benefit in clarifying details for research.
- ChatGPT also assisted in the creation of a make file for ease of compilation and running my executables.

---

## 3. Implementation Details

### 3.1 Overview

This project implements a timing harness for an LRU Profile (Least Recently Used) which replays a fixed trace against the fixed data structure, a hash table. It uses the opcodes, I/E and generates a table full of rich statistics and measurements ment for empirical analysis.

It also implements a trace generator which generates LRU traces and drives a hash table through them, in doing so, collects probe counts and does structural analysis such as provided run-length histograms and additional insight into compaction behavior.

---

### 3.2 Executable + Directory Structure

- **Trace generator:**
  - `project_05_part_2/src/trace-generators/lru_profile/main.cpp`

- **Hash table implementation:**
  - `project_05_part_2/src/implementations/HashTablesOpenAddressing/main.cpp`

- **Replay harness:**
  - `project_05_part_2/src/hash_harness/main.cpp`

- **CSV output directory:**
  - `project_05_part_2/csvs/lru_profile.csv

- **Trace output directory:**
  - `project_05_part_2/traces/lru_profile.trace`

---

### 3.3 How the Generator Works

The LRU generator uses a single fixed RNG seed to produce traces. For each N, it assembles a pool of words in a repeated pattern and then shuffles them. As each word is processed, the generator simulates an LRU cache of size N:

- If a word is already present, it is treated as a hit and moved to the most-recent position.
- If it is not present and the table is not full, it is inserted.
- If the table is full, the least-recently used word is evicted and replaced with the new word.

The output stream consists of I and E operations.  
The number of operations is proportional to N, and the seed controls the shuffle order.

---

### 3.4 Running the Project

From the project home directory, simply type the following commands to either make traces or emit the .csv file via the harness:

**Build and emit traces via trace generator:**

`make traces`

**Build and run harness to emit csv file:**

`make harness`

---
### 3.5 Profile Summary

| Parameter | Value                                |
| --------- | ------------------------------------ |
| Profile   | LRU profile                          |
| Range     | N from 2^10 to 2^20                  |
| N values  | 1024 up to 1,048,576 (powers of two) |
| Seeds     | Single fixed seed (23)               |

### 3.6 CSV Fields

| Column                | Meaning                                  |
|-----------------------|-------------------------------------------|
| impl                  | hash map implementation used              |
| profile               | workload name                             |
| trace_path            | path to the trace file                    |
| N                     | dataset size for the trace                |
| seed                  | RNG seed                                  |
| elapsed_ms            | total replay time                         |
| ops_total             | total operations processed                |
| inserts               | number of insert operations               |
| erases                | number of erase operations                |
| table_size            | table capacity                            |
| active                | number of ACTIVE slots                    |
| available             | number of AVAILABLE slots                 |
| tombstones            | number of DELETED slots                   |
| total_probes          | total probe steps taken                   |
| deletes               | delete operations                         |
| lookups               | lookup operations                         |
| full_scans            | count of full-table scans                 |
| compactions           | compactions triggered                     |
| max_in_table          | max ACTIVE entries seen                   |
| available_pct         | percent AVAILABLE                         |
| load_factor_pct       | percent ACTIVE of table_size              |
| eff_load_factor_pct   | ACTIVE out of (ACTIVE + AVAILABLE)        |
| tombstones_pct        | percent DELETED of table_size             |
| average_probes        | average probes per operation              |
| probe_type            | single or double hashing                  |
| compaction_state      | compaction on/off                         |

---

### 3.7 Visualization

For visualization, the generated CSV can be loaded into the provided D3 HTML plotting tool.  
The application shows probe counts, load factor behavior, and compaction effects for both single and double hashing.  
The curves allow comparison of probe growth, tombstone accumulation, and how compaction changes clustering of the table during the LRU workload.

---

## 4. Testing & Status

### 4.1 What Works

- The timing harness runs as expected and produces a CSV for all tested N values.
- The hash table stand alone application behaves as expected, producing the needed 0/1 map.
- The trace generator compiles and produces traces in the correct format.
- The CSV and TXT outputs load correctly in the plotting and histogram tools.

---

### 4.2 Known Issues / What Does Not Work

- The LRU trace generator produces valid looking traces, but the ordering may not fully match the intended LRU access pattern. It's possible that the shuffle step is not occurring properly.
- Runtime for large N can be slow due to high probe counts and repeated compactions.
- Some metrics seem to fluctuate a bit and are different than other projects seen.

---

### 4.3 How I Tested

- Verified that each trace file followed the expected filename pattern and contained the proper operations.
- Ran the harness on multiple N values from 2^10 to 2^20 and checked that CSV fields populated as expected.
- Loaded both CSV and TXT outputs into the D3 visualization tools to confirm that table behavior was consistent with expectations.

---
