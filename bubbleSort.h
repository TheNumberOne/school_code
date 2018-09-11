#ifndef CS2275_PROJECT_2_BUBBLESORT_H
#define CS2275_PROJECT_2_BUBBLESORT_H

#include <cstddef>
#include <utility>

/**
 * Sorts the array using bubble sort. https://en.wikipedia.org/wiki/Bubble_sort
 * @tparam T the type of elements we're sorting. Must support the &lt; operator
 * and the swap function.
 * @param array the elements to be sorted.
 * @param size the size of array
 */
template <typename T>
void bubbleSort(T* array, size_t size)
{
    size_t sortedLow = size; //All elements including and after this index are sorted.

    //If everything but the first
    //element is sorted, it is necessarily
    //sorted by the fact that there's only once place
    //for it. So we start at index one not zero.
    while (sortedLow > 1)
    {
        size_t highestSwitch = 0; //The highest index of an item that's switched this round.

        for (size_t i = 1; i < sortedLow; i++) {
            if (array[i] < array[i - 1])
            {
                std::swap(array[i], array[i - 1]);
                highestSwitch = i;
            }
        }

        //The highest element that was switched bubbled to the top
        //So we can say it and all elements after it are sorted.
        sortedLow = highestSwitch;
    }
}

#endif //CS2275_PROJECT_2_BUBBLESORT_H
