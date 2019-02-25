//
// Created by thenumberone on 1/30/19.
//

#ifndef HOMEWORK3_RANDLCG1_H
#define HOMEWORK3_RANDLCG1_H

class Randlcg {
public:
    explicit Randlcg(uint32_t seed): state(seed) {}

    double operator()();

private:
    uint32_t state;
    static const uint32_t multiplier = 61;
    static const uint32_t adder = 1;
    static const uint32_t modulus = 1 << 24;
};

#endif //HOMEWORK3_RANDLCG1_H
