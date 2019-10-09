#include "bunny_simulation_report.hpp"

std::ostream &operator<<(std::ostream &out, const bunny_simulation_report &rhs)
{
    out << "Year " << rhs.year << "\n";
    out << "=======================\n";
    
    for (const auto &birth : rhs.births) {
        out << birth.birthed << " was born to " << birth.father << " and " << birth.mother
            << "!\n";
    }
    for (const auto &death : rhs.deaths) {
        out << death << " died!\n";
    }
    for (const auto &infection : rhs.infections) {
        out << infection.infector << " infected " << infection.infected << "!\n";
    }
    
    out << rhs.statistics.num_bunnies << " total bunnies\n";
    
    for (const auto&[gender, frequency] : rhs.statistics.gender_frequencies) {
        out << frequency << " " << gender << " bunnies\n";
    }
    
    out << rhs.statistics.num_mutant_bunnies << " mutant bunnies\n";
    out << rhs.num_births << " bunnies born\n";
    out << rhs.num_deaths << " bunnies died\n";
    
    for (const auto&[age, num_bunnies] : rhs.statistics.age_frequencies) {
        out << num_bunnies << " bunnies are " << age << " years old\n";
    }
    return out;
}

void bunny_simulation_report::report_birth(const bunny &baby, const bunny &mother, const bunny &father)
{
    births.emplace_back(baby, mother, father);
    num_births++;
}

void bunny_simulation_report::report_death(const bunny &bunny)
{
    deaths.push_back(bunny);
    num_deaths++;
}

void bunny_simulation_report::report_infection(const bunny &infected, const bunny &infector)
{
    infections.emplace_back(infected, infector);
}

void bunny_simulation_report::calculate_stats(const std::vector<bunny> &bunnies)
{
    statistics = bunny_statistics(bunnies);
}
