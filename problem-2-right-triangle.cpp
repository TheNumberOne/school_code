
#include <stdexcept>
#include <iostream>
#include "inputHelper.h"

/**
 * Prints a right triangle of stars
 * to standard output with the given number of rows.
 * It uses dashes to pad the triangle. <br/>
 * e.g.
 * printRightTriangle(5) would print<br/>
 * ----*<br/>
 * ---**<br/>
 * --***<br/>
 * -****<br/>
 * *****<br/>
 * @param size the size of the triangle printed
 * @throws std::invalid_argument if size is less than zero.
 */
void printRightTriangle(int size)
{
    if (size < 0) throw std::invalid_argument("size");

    for (int numStars = 1; numStars <= size; numStars++)
    {
        int numDashes = size - numStars;

        for (int j = 0; j < numDashes; j++)
        {
            std::cout << "-";
        }

        for (int j = 0; j < numStars; j++)
        {
            std::cout << '*';
        }

        std::cout << std::endl;
    }
}

/**
 * Prompts for the size of the triangle to print and
 * then prints it.
 * @returns if the user gave valid input or not
 */
int main(int argc, const char **argv)
{
    int size = getPositiveInteger(argc, argv, "Size of triangle: ");
    if (size == -1) return -1;

    printRightTriangle(size);

    return 0;
}