//
// Created by thenumberone on 1/30/19.
//

#include <iostream>
#include "randlcg.hpp"

double Randlcg::operator()() {
    state = (state * multiplier + adder) % modulus;
    return static_cast<double>(state) / modulus;
}