#ifndef CS2275_PROJECT_2_MERGESORT_H
#define CS2275_PROJECT_2_MERGESORT_H

#include <cstddef>
#include <utility>

/**
 * Sorts array using selection sort. https://en.wikipedia.org/wiki/Selection_sort
 * @tparam T The type of elements we are sorting. Must support the &lt; operator
 * and the swap function.
 * @param array The elements to sort.
 * @param size The length of array.
 */
template <typename T>
void selectionSort(T* array, size_t size)
{
    //All elements at the indices before sortFrom have been sorted already.
    for (size_t sortFrom = 0; sortFrom < size - 1; sortFrom++) {
        //The index of the smallest item that hasn't already been sorted.
        size_t firstIndex = sortFrom;

        //Find the smallest element
        for (size_t i = sortFrom + 1; i < size; i++)
        {
            if (array[i] < array[firstIndex]) {
                firstIndex = i;
            }
        }

        //Put the smallest element at the end of the already sorted
        //elements.
        if (firstIndex != sortFrom)
        {
            std::swap(array[firstIndex], array[sortFrom]);
        }
    }
}

#endif //CS2275_PROJECT_2_MERGESORT_H
