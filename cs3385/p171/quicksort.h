#pragma once

// Provides I/O
#include <iostream>

/**
 * Partitions \p a around `a[right]` and returns the ending index of `a[right]`.
 * @param a The array to partition
 * @param left The index of first element to partition
 * @param right The index of the partition.
 * @return The ending index of the partition.
 */
template<typename T>
size_t partition(T *a, size_t left, size_t right) {
    using std::swap;

    // i = beginning of partition >= a[right] rather than ending of partition < a[right]
    size_t i = left;
    for (size_t j = left; j < right; j++)
        if (a[j] < a[right])
            swap(a[j], a[i++]);

    swap(a[right], a[i]);
    return i;
}

/**
 * Sorts \p a using quicksort.
 * @param a The array to sort.
 * @param size The size of \p a
 */
template <typename T>
void quicksort(T *a, size_t size) {
    if (size <= 1) return;

    size_t middle = partition(a, 0, size - 1);
    quicksort(a, middle);
    quicksort(a + middle + 1, size - middle - 1);
}