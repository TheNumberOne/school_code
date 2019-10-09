#include <iostream>
#include <fstream>
#include "bunny.hpp"
#include "bunny_generator.hpp"
#include "bunny_simulation.hpp"

const int num_initial_bunnies = 10;

int main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cerr << "Please pass a valid file name to the program." << std::endl;
        return 1;
    }
    
    auto rng = std::make_shared<std::default_random_engine>(std::random_device()());
    bunny_simulation simulation(num_initial_bunnies, rng);
    
    std::ofstream file;
    file.open(argv[1]);
    
    while (simulation.has_bunnies()) {
        auto report = simulation.simulate_year();
        std::cout << report << std::endl;
        file << report << std::endl;
    }
    
    return 0;
}