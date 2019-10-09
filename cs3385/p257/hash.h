#pragma once

#include <cmath>

// The division method of hashing. See section 11.3.1 of the textbook.
// m is the size of the table
class DivHash {
public:
    int operator()(int key, int m) const {
        return ((unsigned int) key) % m;
    }
};


// The multiplication method of hashing. See section 11.3.2 of the textbook.
// Use the A value suggested in equation 11.2.
// m is the size of the table
class MultHash {
public:
    int operator()(int key, int m) const {
        double _;
        return (int) (m * modf(A * ((unsigned int) key), &_));
    }

private:
    static double constexpr A = (std::sqrt(5) - 1) / 2;
};