#pragma once

// Provides I/O
#include <iostream>
// Provides size_t
#include <cstdlib>
// Provides INT_MAX and INT_MIN
// You can consider INT_MIN to be negative infinity
// and INT_MAX to be infinity
#include <climits>

// This is the struct you will return from your functions.
struct Result {
    // Constructor
    Result(int left_, int right_, int sum_)
            : left(left_), right(right_), sum(sum_) {}

    // Allows comparison between results
    bool operator==(const Result &rhs) {
        return left == rhs.left && right == rhs.right && sum == rhs.sum;
    }

    // Useful for debugging. To use:
    //   Result r(x, y, z);
    //   cout << r << endl;
    friend std::ostream &operator<<(std::ostream &out, const Result &r) {
        out << r.left << " " << r.right << " " << r.sum;
        return out;
    }

    // The data members
    int left, right, sum;
};

/**
 * Finds the maximum subarray that includes elements on both sides of a split array.
 * @param A The array that we are scanning through.
 * @param low The index of the lowest element in the array.
 * @param mid The index of the element to the left of the split.
 * @param high The index of the largest element in the array.
 * @return The start and end indices and total sum of the max subarray.
 */
Result findMaxCrossingSubarray(const int *A, int low, int mid, int high);

/**
 * Finds the maximum non empty subarray of the specified array.
 * @param A The array
 * @param low The index of the first element of it.
 * @param high The index of the last element of it.
 * @return The start and end indices and total sum of the max subarray.
 */
Result findMaxSubarray(const int *A, int low, int high);