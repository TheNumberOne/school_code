#pragma once
#include <cstddef>

/**
 * A tiny wrapper class for automatic deletion of arrays allocated on heap.
 * @tparam T
 */
template<typename T>
class SafeArray {
public:
    explicit SafeArray(size_t len): ptr(new T[len]) { }
    ~SafeArray() { delete[] ptr; }
    T* const ptr;

private:
    // prevent copying so that the ptr isn't deleted multiple times.
    // would use delete in c++11 or higher.
    SafeArray(const SafeArray<T>&);
    SafeArray<T>& operator=(const SafeArray<T>*);
};

/**
 * Copies items in the range [fromStart, fromEnd) to toStart.
 * @tparam T
 * @param fromStart The location to start copying from. Inclusive.
 * @param fromEnd The end of the range to copy from. Exclusive.
 * @param toStart The beginning of the location to start copying to.
 */
template<typename T>
void copy(T* fromStart, T* fromEnd, T* toStart) {
    while (fromStart != fromEnd) {
        *toStart = *fromStart; // Move semantics would be best here.
        fromStart++;
        toStart++;
    }
}

/**
 * Merges two consecutive runs of data together. Heavily modified from page 31 of Introduction to Algorithms 3rd ed.
 *
 * Ideas for improvement: use iterator types to specify the ranges rather than indices
 * like the standard template library does.
 *
 * @tparam T The type of our data.
 * @tparam N The type used to index the data to merge.
 * @param items A pointer to the data.
 * @param start The index of the first item in the left run.
 * @param middle The index of the last item in the left run.
 * @param end The index of the last item in the right run.
 */
template<typename T>
void merge(T* items, ptrdiff_t start, ptrdiff_t middle, ptrdiff_t end) {
    //add 1 for half open ranges
    T* leftStart = items + start;
    T* rightStart = items + middle + 1;
    // would use auto like clang-tidy suggests but that is a c++11 specific feature
    size_t leftLength = static_cast<size_t>(middle - start + 1);
    size_t rightLength = static_cast<size_t>(end - middle);

    //move the runs to merge to outside arrays
    //using RAII to clean up array.
    SafeArray<T> left(leftLength);
    SafeArray<T> right(rightLength);

    copy(leftStart, leftStart + leftLength, left.ptr);
    copy(rightStart, rightStart + rightLength, right.ptr);

    T *i = left.ptr;
    T *j = right.ptr;
    T *iEnd = i + leftLength;
    T *jEnd = j + rightLength;

    for (ptrdiff_t k = start; k <= end; k++) {
        if (j == jEnd || (i != iEnd && *i <= *j)) {
            // would probably use move semantics for increased efficiency if using later version of c++
            items[k] = *i;
            ++i;
        } else {
            // same here. e.g. items[k] = std::move(*j);
            items[k] = *j;
            ++j;
        }
    }
}

/**
 * Sorts the specified items using the merge sort. Modified from page 31 of Introduction to Algorithms 3rd ed.
 *
 * @tparam T The type of our data.
 * @tparam N The type used to index our pointer.
 * @param items A pointer to data.
 * @param start The index of the first element to sort.
 * @param end The index of the last element to sort.
 */
template<typename T>
void mergeSortImpl(T* items, ptrdiff_t start, ptrdiff_t end) {
    if (end <= start) return;

    ptrdiff_t middle = (start + end) / 2;
    mergeSortImpl(items, start, middle);
    mergeSortImpl(items, middle + 1, end);
    merge(items, start, middle, end);
}

/**
 * Sorts the specified items using merge sort.
 *
 * @tparam T The type of our data.
 * @tparam N The type used to index our pointer.
 * @param items A pointer or iterator to our data.
 * @param length The length of our data.
 */
template <typename T>
void mergeSort(T* items, size_t length) {
    mergeSortImpl(items, 0, length - 1);
}

