/**
 * < Rewind Engine > Utils.h
 * Author: DeckardZ46
 * Date: 2024/11/05
 * Note: Misc helper functions for Rewind Engine.
 * Codebase: https://github.com/DeckardZ46/RewindEngine
 */

#pragma once 
#include <chrono>
#include <sstream>

/**
 * time related
 */
enum time_type {
    TIME_COMPLETE = 0,
    TIME_NO_DATE
};

std::string nformat_time(const std::chrono::system_clock::time_point& time_point, time_type type);

/**
 * others
 */
size_t nHashString(std::string str);