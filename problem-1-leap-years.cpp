#include <iostream>

bool isLeapYear(unsigned int year) {
    return year % 4 == 0 && (
            year % 100 != 0 ||
            year % 400 == 0
    );
}

int main() {
    std::cout << "Please input a year: ";

    //I use an int here rather than an unsigned int
    //because cin will read a negative number into an
    //unsigned int without error. Therefore if we want to
    //check if the year is negative, we have to allow it
    //to be signed when input by the user.
    int year;
    std::cin >> year;

    if (!std::cin || year < 0)
    {
        std::cout << "Invalid year." << std::endl;
        return -1;
    }

    if (isLeapYear(static_cast<unsigned int>(year))) {
        std::cout << year << " is a leap year." << std::endl;
    }
    else
    {
        std::cout << year << " is not a leap year." << std::endl;
    }

    return 0;
}

