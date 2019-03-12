
#include "bunny_generator.hpp"
#include "gender.hpp"


bunny random_bunny_generator::operator()()
{
    static const std::vector<std::string> colors{
        "white",
        "brown",
        "black",
        "spotted"
    };
    
    return operator()(colors);
}

bunny random_bunny_generator::operator()(const std::vector<std::string> &colors)
{
    static const std::vector<std::string> genders{
        gender::male,
        gender::female,
        gender::gender_queer
    };
    std::discrete_distribution<> gender_distribution{47, 47, 6};
    
    std::uniform_int_distribution color_distribution{0, (int) (colors.size() - 1)};
    
    static const std::vector<std::string> names{
        "Bunnicula",
        "Fiver",
        "Rabbit",
        "Ruby",
        "Thumper",
        "Mad Hare", // Technically not a rabbit name but shhhhhhhh. Maybe they're a mutant rabbit
        "Peter Rabbit",
        "Bugs Bunny",
        "Hazel",
        "Uncle Wiggily",
        "Br'er Rabbit",
        "God",
        "Rabbit of Caerbannog",
        "Dewdrop",
        "null",
        "Bumbledore",
        "Harry Hopper",
        "Arya",
        "Skaia",
        "Bunquerely Slick",
        "Wabbit"
    };
    std::uniform_int_distribution name_distribution{0, (int) (names.size() - 1)};
    std::discrete_distribution<> mutant_distribution{97, 3};
    
    return {
        genders[gender_distribution(*_rng)],
        colors[color_distribution(*_rng)],
        names[name_distribution(*_rng)],
        (bool) mutant_distribution(*_rng)
    };
}

