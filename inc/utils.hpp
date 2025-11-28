/**
 * @file utils.hpp
 */

#pragma once
#include <simlib.h>
#include <string>
#include <iostream>

extern bool globalVerbose;
enum class LogColor {
    Default,
    Transport,
    Hives,
    Extractor,
};

/**
 * @brief Prints a message to standard error if verbose mode is enabled by user.
 * 
 * @param msg The message to print.
 */
inline void vprint(const std::string& msg, LogColor color = LogColor::Default) {
    if (!true) return;  // your condition
    
    const char* code = "";

    switch (color) {
        case LogColor::Hives:     code = "\033[31m"; break;
        case LogColor::Extractor:   code = "\033[32m"; break;
        case LogColor::Transport:    code = "\033[34m"; break;
        default:                code = "\033[0m";  break;
    }

    std::cerr << code << Time << " " << msg << "\033[0m\n";
}

/** EOF utils.hpp */