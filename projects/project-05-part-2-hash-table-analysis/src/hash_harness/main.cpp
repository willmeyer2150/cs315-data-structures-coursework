// src/harness/hash_harness.cpp

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <iostream>
#include <chrono>
#include <utility>

#include "Operation.hpp"
#include "RunMetaData.hpp"
#include "RunResults.hpp"
#include "../implementations/HashTablesOpenAddressing/HashTableDictionary.hpp"

std::int64_t run_lru_trace(HashTableDictionary &table, const std::vector<Operation> &operations) {

    using clock = std::chrono::steady_clock;
    const int numTrials = 7;

    // Warm up run - Untimed
    table.clear();
    for (const auto &op : operations) {
        switch (op.tag) {
            case OpCode::Insert:
                table.insert(op.key);
                break;
            case OpCode::Erase:
                (void) table.remove(op.key);
                break;
        }
    }

    // Timed runs: 7 passes, take median
    std::vector<std::int64_t> trials_ns;
    trials_ns.reserve(numTrials);

    for (int i= 0; i < numTrials; ++i) {
        table.clear();

        auto t0 = clock::now();
        for (const auto &op : operations) {
            switch (op.tag) {
                case OpCode::Insert:
                    table.insert(op.key);
                    break;
                case OpCode::Erase:
                    (void) table.remove(op.key);
                    break;
            }
        }
        auto t1 = clock::now();

        trials_ns.push_back(std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0).count());
    }

    // Compute Median
    const std::size_t mid = trials_ns.size() / 2;
    std::nth_element(trials_ns.begin(), trials_ns.begin()+mid, trials_ns.end());
    return trials_ns[mid];
}

// Assumes OpCode/Op (with the two arguments) are defined

// The first line of the header must contain:  <profile> <N> <seed>
// After the header: blank lines and lines starting with '#' are okay
// and will be ignored.
// Opcodes: I <key> E <key>

bool load_trace_strict_header(const std::string &path,
                              RunMetaData &runMeta,
                              std::vector<Operation> &out_operations) {
    std::string profile = "";
    int N = 0;
    int seed = 0;
    out_operations.clear();

    std::ifstream in(path);
    if (!in.is_open())
        return false;

    // --- read FIRST line as header
    std::string header;
    if (!std::getline(in, header))
        return false;

    // Look for a non-while-space character
    const auto first = header.find_first_not_of(" \t\r\n");
    // Since this is the first line, we don't expect it to be blank
    // or start with a comment.
    if (first == std::string::npos || header[first] == '#')
        return false;

    // Create a string stream so that we can read the profile name,
    // N, and the seed more easily.
    std::istringstream hdr(header);
    if (!(hdr >> profile >> N >> seed))
        return false;

    runMeta.profile = profile;
    runMeta.N = N;
    runMeta.seed = seed;

    // --- read ops, allowing comments/blank lines AFTER the header ---
    std::string line;
    while (std::getline(in, line)) {
        const auto opCodeIdx = line.find_first_not_of(" \t\r\n");
        if (opCodeIdx == std::string::npos || line[opCodeIdx] == '#')
            continue; // skip blank and comment lines.

        std::istringstream iss(line.substr(opCodeIdx));
        std::string tok; // token: "I" or "E"

        if (!(iss >> tok))
            continue;

        std::string w1, w2; // two words after the op code
        if (tok == "I") {
            if (!(iss >> w1 >> w2)) return false;
            out_operations.emplace_back(OpCode::Insert, w1.append(" ") + w2);
        } else if (tok == "E") {
            if (!(iss >> w1 >> w2)) return false;
            out_operations.emplace_back(OpCode::Erase, w1.append(" ") + w2);
        } else {
            std::cout << "Unknown operation in load_trace_strict_header: " << tok << std::endl;
            return false; // unknown token
        }
    }

    return true;
}


void find_trace_files_or_die(const std::string &dir,
                             const std::string &profile_prefix,
                             std::vector<std::string> &out_files) {
    namespace fs = std::filesystem;
    out_files.clear();

    std::error_code ec;
    fs::path p(dir);

    if (!fs::exists(p, ec)) {
        std::cerr << "Error: directory '" << dir << "' does not exist";
        if (ec) std::cerr << " (" << ec.message() << ")";
        std::cerr << "\n";
        std::exit(1);
    }
    if (!fs::is_directory(p, ec)) {
        std::cerr << "Error: path '" << dir << "' is not a directory";
        if (ec) std::cerr << " (" << ec.message() << ")";
        std::cerr << "\n";
        std::exit(1);
    }

    fs::directory_iterator it(p, ec);
    if (ec) {
        std::cerr << "Error: cannot iterate directory '" << dir << "': "
                << ec.message() << "\n";
        std::exit(1);
    }

    const std::string suffix = ".trace";
    for (const auto &entry: it) {
        if (!entry.is_regular_file(ec)) {
            if (ec) {
                std::cerr << "Error: is_regular_file failed for '"
                        << entry.path().string() << "': " << ec.message() << "\n";
                std::exit(1);
            }
            continue;
        }

        const std::string name = entry.path().filename().string();
        const bool has_prefix = (name.rfind(profile_prefix, 0) == 0);
        const bool has_suffix = name.size() >= suffix.size() &&
                                name.compare(name.size() - suffix.size(),
                                             suffix.size(), suffix) == 0;

        if (has_prefix && has_suffix) {
            out_files.push_back(entry.path().string());
        }
    }

    std::sort(out_files.begin(), out_files.end()); // stable order for reproducibility
}

std::size_t tableSizeForN(std::size_t N) {
    static const std::vector<std::pair<std::size_t, std::size_t>> N_and_primes = {
        /* N = 2^10 = 1,024  */ { 1024,    1279    },
        /* N = 2^11 = 2,048  */ { 2048,    2551    },
        /* N = 2^12 = 4,096  */ { 4096,    5101    },
        /* N = 2^13 = 8,192  */ { 8192,   10273   },
        /* N = 2^14 = 16,384 */ { 16384,   20479   },
        /* N = 2^15 = 32,768 */ { 32768,   40849   },
        /* N = 2^16 = 65,536 */ { 65536,   81931   },
        /* N = 2^17 = 131,072*/ { 131072,  163861  },
        /* N = 2^18 = 262,144*/ { 262144,  327739  },
        /* N = 2^19 = 524,288*/ { 524288,  655243  },
        /* N = 2^20 = 1,048,576*/{ 1048576, 1310809 }
    };

    for (auto item: N_and_primes) {
        if (item.first == N)
            return item.second;
    }
    std::cout << "Unable to find table size for " << N << " in RunMetaData." << std::endl;
    exit(1);
}

int main() {
    const auto profileName = std::string("lru_profile");
    const auto traceDir = std::string("../../traces") + "/" + profileName;
    const auto csvPath = std::string("../../csvs") + "/" + profileName + ".csv";

    // print cwd for debugging
    // std::cout << "cwd: " << std::filesystem::current_path() << "\n";

    std::vector<std::string> traceFiles;
    find_trace_files_or_die(traceDir, profileName, traceFiles);
    /*
    for (auto file: traceFiles) {
        std::cout << file << "\n";
    }
    */
    if (traceFiles.size() == 0) {
        std::cerr << "No trace files found.\n";
        exit(1);
    }

    std::ofstream csv(csvPath);
    if (!csv.is_open()) {
        std::cerr << "Unable to open CSV output file: " << csvPath << std::endl;
        exit(1);
    }

    // Prepen the RunResult Header to the HashTableDictionary Header
    csv << RunResult::csv_header() << "," << HashTableDictionary::csvStatsHeader() << std::endl;

    // loop over all trace files
    for (auto traceFile : traceFiles) {
        const auto pos = traceFile.find_last_of("/\\");
        auto traceFileBaseName = (pos == std::string::npos)
                                    ? traceFile
                                       : traceFile.substr(pos + 1);

        std::vector<Operation> operations;
        RunMetaData run_meta_data;
        load_trace_strict_header(traceFile, run_meta_data, operations);

        // debug message to stdout - traces being loaded
        std::cout << "Loading trace: " << traceFileBaseName
                  << " with N = " << run_meta_data.N
                  << " and " << operations.size() << " operations.\n";

        std::size_t M = tableSizeForN(run_meta_data.N);

        // ============== Single Probe Run ==================
        {
            HashTableDictionary::PROBE_TYPE pType = HashTableDictionary::SINGLE;
            bool doWePerformCompaction = true;

            RunResult result(run_meta_data);
            result.impl         = "hash_map_single";
            result.trace_path   = traceFileBaseName;
            result.profile      = profileName;

            for (const auto &op: operations) {
                if (op.tag == OpCode::Insert) result.inserts++;
                else if (op.tag == OpCode::Erase) result.erases++;
            }

            HashTableDictionary hashTable(M, pType, doWePerformCompaction);

            std::int64_t median_ns = run_lru_trace(hashTable, operations);
            result.elapsed_ns = median_ns;

            double median_ms = result.elapsed_ms();
            std::cout << "Median elapsed_ms for " << traceFileBaseName
                      << " (SINGLE, compaction_on): " << median_ms << " ms\n";

            csv << result.to_csv_row() << "," << hashTable.csvStats() << std::endl;
        }

        // ============== Double Probe Run ==================
    {
        HashTableDictionary::PROBE_TYPE pType = HashTableDictionary::DOUBLE;
        bool doWePerformCompaction = true;

        RunResult result(run_meta_data);
        result.impl         = "hash_map_double";
        result.trace_path   = traceFileBaseName;
        result.profile      = profileName;

        for (const auto &op : operations) {
            if (op.tag == OpCode::Insert) result.inserts++;
            else if (op.tag == OpCode::Erase) result.erases++;
        }

        HashTableDictionary hashTable(M, pType, doWePerformCompaction);

        std::int64_t median_ns = run_lru_trace(hashTable, operations);
        result.elapsed_ns = median_ns;

        double median_ms = result.elapsed_ms();
        std::cout << "Median elapsed_ms for " << traceFileBaseName
                  << " (DOUBLE, compaction_on): " << median_ms << " ms\n";

        csv << result.to_csv_row() << "," << hashTable.csvStats() << std::endl;
    }

    }

    return 0;

}

