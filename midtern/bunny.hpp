#pragma once

#include <utility>
#include <string>
#include <random>

/**
 * Represents a bunny.
 */
class bunny
{
public:
    bunny(std::string gender, std::string color, std::string name, bool mutant) :
        _gender(std::move(gender)),
        _color(std::move(color)),
        _name(std::move(name)),
        _radioactive_mutant_vampire_bunny(mutant),
        _age(0) { }
    
    /**
     * Increases the age of the rabbit by one year.
     */
    void age_year();
    
    const std::string &gender() const;
    
    void gender(const std::string &gender);
    
    const std::string &color() const;
    
    void color(const std::string &color);
    
    uint age() const;
    
    void age(uint age);
    
    const std::string &name() const;
    
    void name(const std::string &name);
    
    bool radioactive_mutant_vampire_bunny() const;
    
    void radioactive_mutant_vampire_bunny(bool radioactive_mutant_vampire_bunny);

private:
    std::string _gender;
    std::string _color;
    uint _age;
    std::string _name;
    bool _radioactive_mutant_vampire_bunny;
};

/**
 * Outputs the bunny to the output stream
 */
std::ostream &operator<<(std::ostream &out, const bunny &rhs);