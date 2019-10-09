//------------------------------------------------------------
// Do not modify this file.
//------------------------------------------------------------

#pragma once

#include <iostream>
#include <string>

class Student {
public:
    Student() {
        _name = "";
        _id = 0;
    }

    Student(const std::string &name, const int id) {
        _name = name;
        _id = id;
    }

    const std::string &name() const { return _name; }

    const int id() const { return _id; }

    bool operator==(const Student &rhs) const {
        return name() == rhs.name() && id() == rhs.id();
    }

    bool operator!=(const Student &rhs) const {
        return !(*this == rhs);
    }

    friend std::ostream &operator<<(std::ostream &out, const Student &p) {
        out << p.name() << " " << p.id();
        return out;
    }

private:
    std::string _name;
    int _id;
};
