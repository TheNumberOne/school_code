#include <algorithm>
#include "bunny_simulation.hpp"
#include "gender.hpp"

std::vector<bunny> generate_bunnies(size_t num_bunnies, random_bunny_generator rbg)
{
    std::vector<bunny> bunnies;
    bunnies.reserve(num_bunnies);
    for (size_t i = 0; i < num_bunnies; i++) {
        bunnies.push_back(rbg());
    }
    return bunnies;
}

bunny_simulation::bunny_simulation(size_t num_bunnies, std::shared_ptr<std::default_random_engine> rng)
    : _rng(rng), _rbg(rng), _bunnies(generate_bunnies(num_bunnies, _rbg))
{
}

bunny_simulation_report bunny_simulation::simulate_year()
{
    year++;
    bunny_simulation_report report(year);
    age_bunnies();
    breed_bunnies(report);
    kill_old_bunnies(report);
    infect_bunnies(report);
    report.calculate_stats(_bunnies);
    return std::move(report);
}

bool bunny_simulation::has_bunnies()
{
    return !_bunnies.empty();
}

void bunny_simulation::age_bunnies()
{
    for (auto &bunny : _bunnies) {
        bunny.age_year();
    }
}

void bunny_simulation::breed_bunnies(bunny_simulation_report &report)
{
    std::vector<bunny> males;
    std::vector<bunny> females;
    
    for (const auto &bunny : _bunnies) {
        if (!is_breedable(bunny)) continue;
        if (bunny.gender() == gender::male) males.push_back(bunny);
        if (bunny.gender() == gender::female) females.push_back(bunny);
    }
    
    std::shuffle(males.begin(), males.end(), *_rng);
    std::shuffle(females.begin(), females.end(), *_rng);
    
    size_t num_pairs = std::min(males.size(), females.size());
    for (size_t i = 0; i < num_pairs; i++) {
        const bunny &father = males[i];
        const bunny &mother = females[i];
        bunny
        baby = _rbg({father.color(), mother.color()});
        _bunnies.push_back(baby);
        report.report_birth(baby, mother, father);
    }
}

bool bunny_simulation::is_breedable(const bunny &bunny) const
{
    return bunny.age() >= 2 && bunny.age() <= 8 && !bunny.radioactive_mutant_vampire_bunny() && (
        bunny.gender() == gender::male ||
        bunny.gender() == gender::female
    );
}

void bunny_simulation::kill_old_bunnies(bunny_simulation_report &report)
{
    for (auto iter = _bunnies.begin(); iter != _bunnies.end();) {
        if (should_die(*iter)) {
            report.report_death(*iter);
            _bunnies.erase(iter);
        } else {
            iter++;
        }
    }
}

bool bunny_simulation::should_die(const bunny &bunny) const
{
    return bunny.radioactive_mutant_vampire_bunny() ? bunny.age() == 50 : bunny.age() > 10;
}

void bunny_simulation::infect_bunnies(bunny_simulation_report &report)
{
    std::vector<const bunny *> vampire_bunnies;
    for (const auto &bunny : _bunnies) {
        if (bunny.radioactive_mutant_vampire_bunny()) {
            vampire_bunnies.push_back(&bunny);
        }
    }
    
    std::vector<bunny *> infectable;
    for (auto &bunny : _bunnies) {
        if (!bunny.radioactive_mutant_vampire_bunny()) {
            infectable.push_back(&bunny);
        }
    }
    
    auto num_to_infect = std::min(infectable.size(), vampire_bunnies.size());
    
    if (num_to_infect == 0) return;
    
    std::vector<bunny *> to_infect;
    std::sample(infectable.begin(), infectable.end(), std::back_inserter(to_infect), num_to_infect, *_rng);
    
    for (size_t i = 0; i < num_to_infect; i++) {
        report.report_infection(*to_infect[i], *vampire_bunnies[i]);
        to_infect[i]->radioactive_mutant_vampire_bunny(true);
    }
}
