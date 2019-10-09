#pragma once

/**
 * Sorts the specified items using an insertion sort.
 * Ideas for improvement:
 * Use std::span type as recommended by CppCoreGuidelines.
 * Convert this into a template function that accepts an array of any type.
 * Change the type of n to size_t.
 *
 * @param items A pointer to an array of items.
 * @param n The number of items in that array.
 */
void insertionSort(int* items, int n);
