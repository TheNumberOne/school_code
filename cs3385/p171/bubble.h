#pragma once

// Provides I/O
#include <iostream>

template<typename T>
void bubblesort(T *A, const int n) {
    using std::swap;

    // This looks more like selection sort than bubble sort.
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (A[j] < A[i]) {
                swap(A[i], A[j]);
            }
        }
    }
}

/**
 * Sorts first \p n elements of \p a in descending order using bubble sort.
 */
template<typename T>
void reverseBubblesort(T *a, size_t n) {
    using std::swap;

    size_t last = n;
    while (last > 0) {
        size_t lastSwapped = 0;
        for (size_t j = 1; j < last; j++) {
            if (a[j - 1] < a[j]) {
                swap(a[j - 1], a[j]);
                lastSwapped = j;
            }
        }
        last = lastSwapped;
    }
}