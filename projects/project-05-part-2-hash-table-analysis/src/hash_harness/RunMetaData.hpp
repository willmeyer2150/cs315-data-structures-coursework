//
// Created by Will Meyer on 11/23/25
//
// src/harness/RunMetaData.hpp
// Metadata about a single trace file for the hash harness.

#pragma once

#include <string>
#include <cstddef>

struct RunMetaData {
    // Name of the profile that generated this trace
    std::string profile;      // e.g., "lru_profice"

    int N   = 0;    // problem size for the trace (e.g., initial inserts)

    int seed = 0;   // RNG seed used to generate the trace
};