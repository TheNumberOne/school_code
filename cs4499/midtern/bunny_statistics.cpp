#include "bunny_statistics.hpp"

bunny_statistics::bunny_statistics(const std::vector<bunny> &bunnies)
    : num_bunnies(bunnies.size())
{
    for (const auto &bunny : bunnies) {
        // specify 0 as default
        gender_frequencies.try_emplace(bunny.gender(), 0);
        gender_frequencies[bunny.gender()]++;
        
        if (bunny.radioactive_mutant_vampire_bunny()) {
            num_mutant_bunnies++;
        }
        
        age_frequencies.try_emplace(bunny.age(), 0);
        age_frequencies[bunny.age()]++;
    }
}
