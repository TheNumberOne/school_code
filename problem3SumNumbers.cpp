
#include <iostream>
#include "inputHelper.h"

/**
 * @author Rosetta Roberts
 *
 * Sums the digits in n in the base 10 number system.
 * @param n
 * @return -1 if n &lt; 0. Otherwise the sum of the digits in n.
 */
int sumDigits(int n) {
    if (n < 0) return -1;

    int sum = 0;
    while (n > 0) {
        //Add the last digit from n to sum
        sum += n % 10;

        //Remove the last digit from n
        n /= 10;
    }

    return sum;
}

/**
 * @author Rosetta Roberts
 *
 * Reads in an integer and then prints out the sum of its digits.
 *
 * @return 0 if the program ran successfully
 */
int main(int argc, char **argv) {
    int num;
    if (!readInt(num, argc, argv, "Please input an integer: ", false)) return -1;

    int sum = sumDigits(num);

    std::cout << "Sum of digits: " << sum << std::endl;

    return 0;
}