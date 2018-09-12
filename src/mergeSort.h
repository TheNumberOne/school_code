/**
 * @author Rosetta Roberts
 */

#ifndef CS2275_PROJECT_2_TIMSORT_H
#define CS2275_PROJECT_2_TIMSORT_H

#include <cstddef>
#include <memory>

template<typename T>
static void merge(T *start, T *middle, T *end, T *to);

/**
 * Sorts array using merge sort. https://en.wikipedia.org/wiki/Merge_sort
 * @tparam T The type of elements in the array.
 * Must support the &lt; operator and move assignment.
 * @param array The elements to sort.
 * @param size The number of elements in array.
 */
template<typename T>
void mergeSort(T *array, size_t size) {
    //Using buffer so that it is automatically deleted at end of function.
    auto buffer = std::make_unique<T[]>(size);

    T *from = array;
    T *to = buffer.get();

    for (size_t mergeLength = 1; mergeLength < size; mergeLength *= 2) {
        size_t i = 0;

        //Merge runs of equal length.
        for (; i + 2 * mergeLength <= size; i += 2 * mergeLength) {
            merge(from + i, from + i + mergeLength, from + i + 2 * mergeLength, to + i);
        }

        if (i + mergeLength < size) {
            //Merge last two runs of unequal length
            merge(from + i, from + i + mergeLength, from + size, to + i);
        } else if (i < size) {
            //Last run isn't paired so we just copy it over
            std::move(from + i, from + size, to + i);
        }

        std::swap(from, to);
    }

    //If the end result is at the wrong place, move it
    //to the input array.
    if (from != array) {
        std::move(from, from + size, array);
    }
}

/**
 * Merges two runs into the array pointed by to.
 * @param start Points to the start of the first run.
 * @param middle Points to the element after the last element of the first run
 * and the first element of the second run.
 * @param end Points to the element after the last element.
 * @param to Points to the location to merge the elements to.
 */
template<typename T>
static void merge(T *start, T *middle, T *end, T *to) {
    //Points to the element we are merging in first run.
    T *a = start;
    //Points to the element we are merging in the second run.
    T *b = middle;

    //Merge the runs until we run to the end of the run.
    while (a != middle && b != end) {
        //Keep *a first on tie to maintain stability.
        if (*b < *a) {
            *(to++) = std::move(*(b++));
        } else {
            *(to++) = std::move(*(a++));
        }
    }

    //Move remaining elements
    if (a != middle && b == end) {
        std::move(a, middle, to);
    } else if (a == middle && b != end) {
        std::move(b, end, to);
    }
}

#endif //CS2275_PROJECT_2_TIMSORT_H
