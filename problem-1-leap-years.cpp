#include <iostream>
#include "inputHelper.h"

/**
 * @author Rosetta Roberts
 * @param year
 * @return Whether the passed year is a leap year
 */
bool isLeapYear(unsigned int year) {
    // A leap year is divisible by four,
    // except for multiples of 100, unless
    // it is also a multiple of 400.

    return year % 4 == 0 && (
            year % 100 != 0 ||
            year % 400 == 0
    );
}

/**
 * Prompts the user for a year and then displays if it is a
 * leap year or not.
 * @return 0 if user input was valid
 */
int main(int argc, const char **argv) {
    int year;
    if (!readInt(year, argc, argv, "Please input a year: ", true)) return -1;

    if (isLeapYear(static_cast<unsigned int>(year))) {
        std::cout << year << " is a leap year." << std::endl;
    } else {
        std::cout << year << " is not a leap year." << std::endl;
    }

    return 0;
}

