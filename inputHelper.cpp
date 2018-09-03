

#include <string>
#include <stdexcept>
#include <iostream>

/**
 * @author Rosetta Roberts
 * Tries to parse the given string into an integer.
 * If there is a problem, passes an error to the passed stream.
 * @param string the string to parse.
 * @param parsed if the string is a valid positive integer, it will
 * be filled.
 * @param errorStream the stream to send error messages to.
 * @return whether parsing was successful.
 */
static bool tryParsePositiveInteger(const std::string &string, int &parsed, std::ostream &errorStream) {
    try {
        parsed = std::stoi(string);

        if (parsed >= 0) {
            return true;
        }

        errorStream << "Please specify a positive number." << std::endl;
    }
    catch (std::invalid_argument &e) {
        errorStream << "Please specify a valid number." << std::endl;
    }
    catch (std::out_of_range &e) {
        errorStream << "Number too large." << std::endl;
    }

    return false;
}

/**
 * @author Rosetta Roberts
 * Reads a positive integer from either the command line
 * or from stdin. Will first attempt to read the first command
 * line argument. If an argument is provided and it is not
 * a positive integer or it is not provided and stdin is closed,
 * this will return -1.
 * @param argc the number of arguments passed to the program.
 * @param argv the arguments passed to the program
 * @param prompt the prompt to use if the number isn't passed in as
 *  an argument to the program.
 * @return a positive integer.
 */
int getPositiveInteger(int argc, const char **argv, const char *prompt) {
    if (argc > 1) {
        //Try to parse command line arguments.
        int num;

        if (tryParsePositiveInteger(argv[1], num, std::cerr)) {
            return num;
        }
    } else {
        //Loop until the user passes a positive integer.
        while (std::cin) {
            std::cout << prompt;

            std::string input;
            std::getline(std::cin, input);

            int num;
            if (tryParsePositiveInteger(input, num, std::cout)) {
                return num;
            }
        }

        std::cerr << "Unable to read positive integer from standard input." << std::endl;
    }

    return -1;
}
