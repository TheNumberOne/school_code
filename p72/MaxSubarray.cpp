#include "./MaxSubarray.h"
#include "MaxSubarray.h"

#include <iostream>
// Provides floor, ceil, etc.
#include <cmath>
#include <cassert>

/**
 * Finds the maximum subarray on the left side that includes A[mid]
 * and finds the maximum subarray on the right side that includes A[mid + 1] and
 * returns the concatenation of the two.
 */
Result findMaxCrossingSubarray(const int *A, int low, int mid, int high) {
    assert(low <= mid && mid < high);

    int maxLeftSum = INT_MIN;
    int maxLeftIndex = 0;
    int sum = 0;

    for (int i = mid; i >= low; i--) {
        sum += A[i];
        if (sum > maxLeftSum) {
            maxLeftSum = sum;
            maxLeftIndex = i;
        }
    }

    int maxRightSum = INT_MIN;
    int maxRightIndex = 0;
    sum = 0;
    for (int i = mid + 1; i <= high; i++) {
        sum += A[i];
        if (sum > maxRightSum) {
            maxRightSum = sum;
            maxRightIndex = i;
        }
        maxRightSum = std::max(maxRightSum, sum);
    }

    return Result(maxLeftIndex, maxRightIndex, maxLeftSum + maxRightSum);
}

/**
 * Calculates the floored integer division between its arguments.
 */
static int floorDiv(int a, int b) {
    return static_cast<int>(floor(static_cast<double>(a) / b));
}

/**
 * Finds the maximum subarray by splitting the array, searching both sides for the max subarray,
 * finding the max subarray that crosses the middle, and then returning the max subarray of those three.
 * Should have an Theta(n*log(n)) time. A more efficient algorithm that can run in Theta(n) time is possible.
 *
 * Implementation of more efficient algorithm is down below.
 *
 */
Result findMaxSubarray(const int *A, int low, int high) {
    assert(low <= high);

    if (low == high) {
        return Result(low, high, A[low]);
    }

    int mid = floorDiv(low + high, 2);

    Result left = findMaxSubarray(A, low, mid);
    Result cross = findMaxCrossingSubarray(A, low, mid, high);
    Result right = findMaxSubarray(A, mid + 1, high);

    if (left.sum >= cross.sum) {
        if (left.sum >= right.sum) {
            return left;
        } else {
            return right;
        }
    } else if (cross.sum >= right.sum) {
        return cross;
    } else {
        return right;
    }
}

//Result findMaxSubarray(const int *A, int low, int high) {
//    int sum = A[low];
//    int i = low;
//    int maxSum = sum;
//    int maxStart = i;
//    int maxEnd = i;
//
//    for (int j = low + 1; j <= high; j++) {
//        if (sum < 0) {
//            sum = A[j];
//            i = j;
//        } else {
//            sum += A[j];
//        }
//
//        if (sum > maxSum) {
//            maxSum = sum;
//            maxStart = i;
//            maxEnd = j;
//        }
//    }
//
//    return Result(maxStart, maxEnd, maxSum);
//}