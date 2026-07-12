// ===============================================================
// File:    utils.cpp
// Project: Project_03_Meyer_GPT_Edit
// Author:  (original) Prof. Ali Kooshesh
// Edits:   Will Meyer (bannering and organization only)
// Date:    2025-11-09
// Purpose: Implementation of common utilities and error handling.
//          NOTE: Behavior kept identical to professor’s original.
// ===============================================================

#include "utils.hpp"

// ---------------------------------------------------------------
// Section 1: Includes
// ---------------------------------------------------------------
#include <iostream>
#include <filesystem>
#include <fstream>

// ---------------------------------------------------------------
// Section 2: Error Handling
// ---------------------------------------------------------------
void exitOnError(error_type error, const std::string &entityName) {
    switch (error) {
        case NO_ERROR:
            // do nothing
            return;

        case FILE_NOT_FOUND:
            std::cerr << "Error: File " << entityName << " doesn't exist. Terminating...\n";
            std::exit(FILE_NOT_FOUND);

        case UNABLE_TO_OPEN_FILE:
            std::cerr << "Error: Unable to open '" << entityName << "'. Terminating...\n";
            std::exit(UNABLE_TO_OPEN_FILE);

        case DIR_NOT_FOUND:
            std::cerr << "Error: Directory " << entityName << " doesn't exist. Terminating...\n";
            std::exit(DIR_NOT_FOUND);

        case UNABLE_TO_OPEN_FILE_FOR_WRITING:
            std::cerr << "Error: Unable to open " << entityName << " for writing. Terminating...\n";
            std::exit(UNABLE_TO_OPEN_FILE_FOR_WRITING);

        default:
            std::cerr << "Error: Unknown error type. Terminating...\n";
            std::exit(ERR_TYPE_NOT_FOUND);
    }
}

// ---------------------------------------------------------------
// Section 3: Filesystem Checks
// ---------------------------------------------------------------
error_type directoryExists(const std::string &name) {
    if (!std::filesystem::is_directory(name)) {
        return DIR_NOT_FOUND;
    }
    return NO_ERROR;
}

error_type regularFileExists(const std::string &name) {
    if (!std::filesystem::is_regular_file(name)) {
        return FILE_NOT_FOUND;
    }
    return NO_ERROR;
}

error_type regularFileExistsAndIsAvailable(const std::string &filename) {
    if (error_type rv; (rv = regularFileExists(filename)) != NO_ERROR) {
        return rv;
    }
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        return UNABLE_TO_OPEN_FILE;
    }
    infile.close();
    return NO_ERROR;
}

// (Kept declaration for compatibility if used elsewhere)
error_type fileExists(const std::string &name); // no definition provided in original

// ---------------------------------------------------------------
// Section 4: Path / Name Utilities
// ---------------------------------------------------------------
std::string baseNameWithoutTxt(const std::string& filename) {
    namespace fs = std::filesystem;
    fs::path p(filename);

    // strip .txt if present
    if (p.extension() == ".txt") {
        return p.stem().string();
    }
    return p.filename().string();
}

// ---------------------------------------------------------------
// Section 5: File Write Helpers
// ---------------------------------------------------------------
error_type canOpenForWriting(const std::string& filename) {
    std::ofstream out(filename, std::ios::out | std::ios::trunc);
    const bool ok = out.is_open();
    out.close();
    return ok ? NO_ERROR : UNABLE_TO_OPEN_FILE_FOR_WRITING;
}

error_type writeVectorToFile(const std::string& filename,
                             const std::vector<std::string>& data) {
    std::ofstream out(filename, std::ios::out | std::ios::trunc);
    if (!out.is_open()) {
        return UNABLE_TO_OPEN_FILE_FOR_WRITING;
    }

    for (const auto& item : data) {
        out << item << '\n';
        if (!out) {
            std::cerr << "Error: failed while writing to " << filename << "\n";
            return FAILED_TO_WRITE_FILE;
        }
    }
    return NO_ERROR;
}
