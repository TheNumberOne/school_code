#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <ctime>
#include "bubbleSort.h"
#include "selectionSort.h"
#include "mergeSort.h"

using namespace std;

unique_ptr<int[]> readFile(const string &fileName, size_t &length);

void printUsage(char *programName);

/**
 * Opens the file at the first argument and
 * then sorts the numbers in it by the sort
 * specified with the second argument.
 */
int main(int argc, char *argv[]) {
    if (argc < 3) {
        printUsage(argv[0]);
        return 1;
    }
    size_t length = 0;
    unique_ptr<int[]> array = readFile(argv[1], length);

    long sortType = strtol(argv[2], nullptr, 10);

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

    double milliseconds = double(end - start) / CLOCKS_PER_SEC * 1000;

    for (size_t i = 0; i < length; i++)
    {
        printf("%d\n", array[i]);
    }

    printf("Took %f ms.\n", milliseconds);

    return 0;
}

/**
 * Reads a file from fileName into an array.
 * The file must start with an integer saying how many other
 * integers are in the file. Each integer is then specified on
 * its own line in the file. e.g.:
 * 3
 * 123
 * -4
 * 42
 * @param fileName the name of the file to read from.
 * @param length populated with the number of integers returned.
 * @return the number of integers in the file except.
 * for the first one specifying the number of integers.
 */
unique_ptr<int[]> readFile(const string &fileName, size_t &length) {
    ifstream file(fileName);

    file >> length;

    //Using unique pointer instead of raw pointer
    //so RAII deletes the pointer when no longer in use
    //rather than me having to worry about it and
    //be paranoid about exceptions evading delete statements.
    auto array = std::make_unique<int[]>(length);
    size_t i = 0;

    while (!file.eof() && i < length) {
        file >> array[i++];
    }
    file.close();

    return array;
}

/**
 * Prints how to use this program to stdout.
 * @param programName the name of the program.
 */
void printUsage(char *programName) {
    printf("Usage: %s filename sortToUse\n", programName);
    printf("  sortToUse (input a listed number):\n");
    printf("    1: Bubble Sort\n");
    printf("    2: Selection Sort\n");
    printf("    3: Tim Sort\n");
}
