#pragma once


#include <cstddef>
#include <map>
#include "bunny.hpp"

/**
 * Represents various statistics on a bunny population
 */
struct bunny_statistics
{
    bunny_statistics() = default;
    
    explicit bunny_statistics(const std::vector<bunny> &bunnies);
    
    unsigned long num_bunnies = 0;
    unsigned long num_mutant_bunnies = 0;
    std::map<std::string, int> gender_frequencies;
    std::map<int, int> age_frequencies;
};


