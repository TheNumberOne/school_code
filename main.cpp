#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "bubbleSort.h"
#include "selectionSort.h"
#include "mergeSort.h"

using namespace std;

unique_ptr<int[]> readFile(const string &fileName, size_t &length);

void printUsage(char *programName);

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printUsage(argv[0]);
        return 1;
    }

    long sortType = strtol(argv[2], nullptr, 10);

    size_t length = 0;
    unique_ptr<int[]> array = readFile(argv[1], length);

    clock_t start = clock();

    switch (sortType) {
        case 1:
            bubbleSort(array.get(), length);
            break;
        case 2:
            selectionSort(array.get(), length);
            break;
        case 3:
            mergeSort(array.get(), length);
            break;
        default:
            printf("Invalid sort.\n");
            printUsage(argv[0]);
            return 1;
    }

    clock_t end = clock();

    double milliseconds = double(end - start) / CLOCKS_PER_SEC / 1000;

    for (size_t i = 0; i < length; i++)
    {
        printf("%d\n", array[i]);
    }

    printf("Took %f ms.\n", milliseconds);

    return 0;
}

unique_ptr<int[]> readFile(const string &fileName, size_t &length) {
    ifstream file(fileName);

    file >> length;

    //Using unique pointer instead of raw pointer
    //so that it would automatically be destroyed
    //when no longer being used
    auto array = std::make_unique<int[]>(static_cast<size_t>(length));
    size_t i = 0;

    while (!file.eof()) {
        file >> array[i++];
    }
    file.close();

    return array;
}

void printUsage(char *programName) {
    printf("Usage: %s filename sortToUse\n", programName);
    printf("  sortToUse (input a listed number):\n");
    printf("    1: Bubble Sort\n");
    printf("    2: Selection Sort\n");
    printf("    3: Tim Sort\n");
}
