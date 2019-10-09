#include "bunny.hpp"
#include <ostream>

void bunny::age_year()
{
    _age++;
}

const std::string &bunny::gender() const
{
    return _gender;
}

void bunny::gender(const std::string &gender)
{
    _gender = gender;
}

const std::string &bunny::color() const
{
    return _color;
}

void bunny::color(const std::string &color)
{
    _color = color;
}

unsigned int bunny::age() const
{
    return _age;
}

void bunny::age(unsigned int age)
{
    _age = age;
}

const std::string &bunny::name() const
{
    return _name;
}

void bunny::name(const std::string &name)
{
    _name = name;
}

bool bunny::radioactive_mutant_vampire_bunny() const
{
    return _radioactive_mutant_vampire_bunny;
}

void bunny::radioactive_mutant_vampire_bunny(bool radioactive_mutant_vampire_bunny)
{
    _radioactive_mutant_vampire_bunny = radioactive_mutant_vampire_bunny;
}

std::ostream &operator<<(std::ostream &out, const bunny &rhs)
{
    out << rhs.name() << "(";
    if (rhs.radioactive_mutant_vampire_bunny()) {
        out << "mutant, ";
    }
    out << rhs.age() << ", "
        << rhs.gender() << ", "
        << rhs.color() << ")";
    return out;
}
