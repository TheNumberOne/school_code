#pragma once

#include "bunny.hpp"
#include <utility>
#include <memory>

/**
 * Randomly generates rabbits using the passed random number generator.
 */
class random_bunny_generator
{
public:
    explicit random_bunny_generator(std::shared_ptr<std::default_random_engine> rng) : _rng(std::move(rng)) { }
    
    /**
     * Creates a randomly generated bunny.
     */
    bunny operator()();
    
    /**
     * Creates a randomly generated bunny using the specified colors. Mostly used for when two rabbits have a child.
     */
    bunny operator()(const std::vector<std::string> &colors);

private:
    /**
     * Rng used
     */
    std::shared_ptr<std::default_random_engine> _rng;
};