#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <set>
#include "randlcg.hpp"

double findMean(Randlcg rand, int count) {
    double total = 0;

    for (int i = 0; i < count; i++) {
        total += rand();
    }

    return total / count;
}

std::vector<int> bin(Randlcg rand, size_t numBins, int count) {
    std::vector<int> bins(numBins, 0);

    for (int i = 0; i < count; i++) {
        double r = rand();
        int bin = static_cast<int>(r * numBins);
        bins[bin]++;
    }

    return bins;
}

int periodOf(Randlcg r) {
    std::set<double> elementsCreated;

    while (true) {
        auto [_, unique] = elementsCreated.insert(r());
        if (!unique) {
            break;
        }
    }

    return static_cast<int>(elementsCreated.size());
}

static const int RAND_SEED = 100001;

int main() {
    std::vector<int> sizes{100, 10000, 1000000, 100000000};

    for (int size : sizes) {
        Randlcg rand{RAND_SEED};
        std::cout << "Mean of first " << size << " elements is " << findMean(rand, size) << std::endl;
    }

    for (int size : sizes) {
        Randlcg rand{RAND_SEED};
        auto bins = bin(rand, 100, size);

        std::cout << "Histogram of " << size << " elements is: " << std::endl;
        std::copy(bins.begin(), bins.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }

    std::cout << "Period is " << periodOf(Randlcg{RAND_SEED}) << std::endl;

    return 0;
}

