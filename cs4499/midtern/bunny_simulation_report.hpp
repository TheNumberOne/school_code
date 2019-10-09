#pragma once

#include "bunny.hpp"
#include "bunny_statistics.hpp"
#include <utility>
#include <ostream>

/**
 * Represents a bunny's birth.
 */
struct bunny_birth
{
    bunny_birth(bunny birthed, bunny mother, bunny father)
        : birthed(std::move(birthed)), mother(std::move(mother)), father(std::move(father)) { }
    
    bunny birthed;
    bunny mother;
    bunny father;
};

/**
 * Represents a bunny getting infected.
 */
struct bunny_infection
{
    bunny_infection(bunny infected, bunny infector) : infected(std::move(infected)), infector(std::move(infector)) { }
    
    bunny infected;
    bunny infector;
};

/**
 * Represents a report for a turn in the simulation.
 */
struct bunny_simulation_report
{
    explicit bunny_simulation_report(int year) : year(year) { }
    
    /**
     * Report the birth of a bunny
     * @param baby The bunny born
     * @param mother The mother
     * @param father The father
     */
    void report_birth(const bunny &baby, const bunny &mother, const bunny &father);
    
    /**
     * Reports a bunny getting infected.
     * @param infected The infected bunny
     * @param infector The infecting bunny
     */
    void report_infection(const bunny &infected, const bunny &infector);
    
    /**
     * Reports a bunny dying
     * @param bunny the bunny that died
     */
    void report_death(const bunny &bunny);
    
    /**
     * Calculates various statistics for the bunnies and adds them to the report.
     * @param bunnies
     */
    void calculate_stats(const std::vector<bunny> &bunnies);
    
    /**
     * The year the report was generated for
     */
    int year;
    
    /**
     * Birth events
     */
    std::vector<bunny_birth> births;
    
    /**
     * Death events
     */
    std::vector<bunny> deaths;
    
    /**
     * Infection events.
     */
    std::vector<bunny_infection> infections;
    
    /**
     * Statistics of the current population.
     */
    bunny_statistics statistics;
    
    /**
     * total number of births in this year
     */
    size_t num_births = 0;
    
    /**
     * Total number of deaths in this year.
     */
    size_t num_deaths = 0;
};

/**
 * outputs the report
 */
std::ostream &operator<<(std::ostream &out, const bunny_simulation_report &rhs);
