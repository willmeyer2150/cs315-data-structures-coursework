// ===============================================================
// File:    utils.hpp
// Project: Project_03_Meyer_GPT_Edit
// Author:  (original) Prof. Ali Kooshesh
// Edits:   Will Meyer (bannering and organization only)
// Date:    2025-11-09
// Purpose: Common utility functions and error codes:
//          - file/dir existence checks
//          - safe open-for-writing checks
//          - vector<string> -> file writer
//          - error handling via exitOnError()
// ===============================================================

#pragma once
#ifndef IMPLEMENTATION_UTILS_HPP
#define IMPLEMENTATION_UTILS_HPP

// ---------------------------------------------------------------
// Section: Includes
// ---------------------------------------------------------------
#include <string>
#include <vector>

// ---------------------------------------------------------------
// Section: Error Codes
// ---------------------------------------------------------------
enum error_type {
    NO_ERROR,
    FILE_NOT_FOUND,
    DIR_NOT_FOUND,
    UNABLE_TO_OPEN_FILE,
    ERR_TYPE_NOT_FOUND,
    UNABLE_TO_OPEN_FILE_FOR_WRITING,
    FAILED_TO_WRITE_FILE,
};

// ---------------------------------------------------------------
// Section: API
// ---------------------------------------------------------------
void        exitOnError(error_type error, const std::string& entityName);
error_type  regularFileExistsAndIsAvailable(const std::string& fileName);
error_type  fileExists(const std::string& name);              // (decl retained if used elsewhere)
error_type  directoryExists(const std::string& name);
error_type  regularFileExists(const std::string& name);
std::string baseNameWithoutTxt(const std::string& filename);
error_type  canOpenForWriting(const std::string& filename);
error_type  writeVectorToFile(const std::string& filename,
                              const std::vector<std::string>& lines);

#endif // IMPLEMENTATION_UTILS_HPP
