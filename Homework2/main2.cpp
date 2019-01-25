#include <iostream>

class Randlcg {
public:
    explicit Randlcg(uint32_t seed): state(seed) {}

    double operator()() {
        state = (state * multiplier + adder) % modulus;
        return static_cast<double>(state) / modulus;
    }

private:
    uint32_t state;
    static const uint32_t multiplier = 61;
    static const uint32_t adder = 1;
    static const uint32_t modulus = 1 << 24;
};

int main() {
    Randlcg randlcg { 100001 };

    for (auto i = 0; i < 30; i++){
        std::cout << randlcg() << std::endl;
    }

    return 0;
}