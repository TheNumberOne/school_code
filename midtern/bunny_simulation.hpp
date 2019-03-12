#pragma once


#include <vector>
#include "bunny.hpp"
#include "bunny_generator.hpp"
#include "bunny_simulation_report.hpp"

class bunny_simulation
{
public:
    explicit bunny_simulation(size_t num_bunnies, std::shared_ptr<std::default_random_engine> rng);
    
    /**
     * Simulates a year for the rabbits.
     */
    bunny_simulation_report simulate_year();
    
    /**
     * true if there are still bunnies alive
     */
    bool has_bunnies();

private:
    uint year = 0;
    std::shared_ptr<std::default_random_engine> _rng;
    random_bunny_generator _rbg;
    std::vector<bunny> _bunnies;
    
    /**
     * Increases the age of all bunnies by one year
     */
    void age_bunnies();
    
    /**
     * Breeds the bunnies together
     */
    void breed_bunnies(bunny_simulation_report &report);
    
    /**
     * Kills old bunnies.
     */
    void kill_old_bunnies(bunny_simulation_report &report);
    
    /**
     * Causes radioactive mutant vampire bunnies to spread.
     */
    void infect_bunnies(bunny_simulation_report &report);
    
    /**
     * Determines if a bunny is breedable.
     */
    bool is_breedable(const bunny &bunny) const;
    
    /**
     * Determines if a bunny should die or not.
     */
    bool should_die(const bunny &bunny) const;
};


