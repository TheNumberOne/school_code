#pragma once

#include <utility>
#include <cstddef>

/**
 * Inspired by the insertion sort used for small arrays of simple type
 * in java.utils.Arrays of openjdk-8
 */
template <typename T>
void insertionSort(T* items, size_t n) {
    //Using std::swap so that minimal changes would have to be made if this was converted to a template function.
    using std::swap;

    for (size_t i = 1; i < n; i++)
        for (size_t j = i; j > 0 && items[j-1] > items[j]; j--)
            swap(items[j], items[j-1]);
}
