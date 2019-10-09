#include <utility>
#include "./InsertionSort.h"

/**
 * Inspired by the insertion sort used for small arrays of simple type
 * in java.utils.Arrays of openjdk-8
 */
void insertionSort(int* items, int n) {
    //Using std::swap so that minimal changes would have to be made if this was converted to a template function.
    using std::swap;

    //Using decltype so that if the type of n is changed, i and j automatically update to same type.
    for (decltype(n) i = 1; i < n; i++)
        for (decltype(n) j = i; j > 0 && items[j-1] > items[j]; j--)
            swap(items[j], items[j-1]);
}
