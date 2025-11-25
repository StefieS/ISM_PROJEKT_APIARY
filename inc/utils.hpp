/**
 * @file utils.hpp
 */

#pragma once

#include <string>
#include <iostream>

extern bool globalVerbose;

/**
 * @brief Prints a message to standard error if verbose mode is enabled by user.
 * 
 * @param msg The message to print.
 */
inline void vprint(const std::string& msg) {
    if (globalVerbose) std::cerr << msg << "\n";
}

/** EOF utils.hpp */