#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void printUsage(char *programName);

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printUsage(argv[0]);
        return 1;
    }
    string filename = argv[1];
    ifstream file(filename);
    int input;
    file >> input;
    int numberOfEntries = input;

    // Might need to put some array here
    while (!file.eof()) {
        file >> input;
        // do something with input
    }
    file.close();

    // Sort array as requested

    return 0;
}

void printUsage(char *programName) {
    printf("Usage: %s filename sortToUse\n", programName);
    printf("  sortToUse (input a listed number):\n");
    printf("    1: Bubble Sort\n");
    printf("    2: Merge Sort\n");
    printf("    3: [Other sort here]\n");
}
