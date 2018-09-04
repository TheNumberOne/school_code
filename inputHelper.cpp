

#include <string>
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
static bool tryParseInt(const std::string &string, int &parsed, std::ostream &errorStream, bool nonNegative) {
    try {
        parsed = std::stoi(string);

        if (!nonNegative || parsed >= 0) {
            return true;
        }

        errorStream << "Please specify a non negative number." << std::endl;
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
 *
 * Reads an integer from either the command line
 * or from stdin. Will first attempt to read the first command
 * line argument. Returns whether it was successful at reading an integer.
 *
 * @param result read the integer into this variable
 * @param argc the number of arguments passed to the program.
 * @param argv the arguments passed to the program
 * @param prompt the prompt to use if the number isn't passed in as
 *  an argument to the program.
 * @param nonNegative if the integer read in should be non negative
 * @return whether this was able to successfully read an integer or not.
 */
bool readInt(int &result, int argc, const char *const *argv, const char *prompt, bool nonNegative) {
    if (argc > 1) {
        if (tryParseInt(argv[1], result, std::cerr, nonNegative)) {
            return true;
        }

        std::cerr << "Invalid command line argument." << std::endl;
    } else {
        //Loop until the user passes a nonNegative integer.
        while (std::cin) {
            std::cout << prompt;

            std::string input;
            std::getline(std::cin, input);

            if (tryParseInt(input, result, std::cout, nonNegative)) {
                return true;
            }
        }

        std::cerr << "Unable to read an integer from standard input." << std::endl;
    }

    return false;
}
