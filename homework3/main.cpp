#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <set>
#include <dialog.h>
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

void printHistogram(const std::vector<int> &bars, int max, const std::vector<std::string>& rowLabels) {
    for (int i = 0; i < bars.size(); i++) {
        int bar = bars[i];
        int width = static_cast<int>(std::round(bar * 10000.0 / max));
        std::cout << rowLabels[i];
        for (int j = 0; j < width; j++) {
            std::cout << "#";
        }
        std::cout << std::endl;
    }
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

std::vector<std::string> generateLabels();

int main() {
    std::vector<int> sizes{100, 10000, 1000000, 100000000};

    for (int size : sizes) {
        Randlcg rand{RAND_SEED};
        std::cout << "Mean of first " << size << " elements is " << findMean(rand, size) << std::endl;
    }

    std::vector<std::string> labels = generateLabels();

    for (int size : sizes) {
        Randlcg rand{RAND_SEED};
        auto bins = bin(rand, 100, size);

        std::cout << "Histogram of " << size << " elements is:" << std::endl;
        printHistogram(bins, size, labels);
    }

    std::cout << "Period is " << periodOf(Randlcg{RAND_SEED}) << std::endl;

    return 0;
}

std::vector<std::string> generateLabels() {
    std::vector<std::string> labels;

    for (int i = 0; i < 100; i++) {
        std::ostringstream ss;
        ss.precision(2);
        ss << std::fixed;
        ss << i/100.0 << "-" << (i + 1)/100.0 << ": ";
        labels.push_back(ss.str());
    }
    return labels;
}