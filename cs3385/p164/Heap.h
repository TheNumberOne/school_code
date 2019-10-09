#pragma once

// Provides I/O
#include <iostream>
// Provides size_t
#include <cstdlib>
// Provides INT_MAX and INT_MIN
// You can consider INT_MIN to be negative infinity
// and INT_MAX to be infinity
#include <climits>
#include "Patient.h"

/**
 * Helper class to manage an array pointer.
 * @tparam T The array type.
 */
template<typename T>
class Array {
public:
    /**
     * Creates an array of the specified size.
     * @param size The size of the array.
     */
    explicit Array(size_t size) : mVal(new T[size]), mSize(size) {}

    ~Array() { delete[] mVal; }


    T &operator[](size_t index) {
        return mVal[index];
    }

    const T &operator[](size_t index) const {
        return mVal[index];
    }

    Array(const Array &rhs) : mVal(new T[rhs.mSize]), mSize(rhs.mSize) {
        std::copy(rhs.mVal, rhs.mVal + rhs.mSize, mVal);
    }

    Array &operator=(const Array &rhs) {
        Array copy = rhs;
        swap(copy);
        return *this;
    }

    void swap(Array &rhs) {
        using std::swap;
        swap(mVal, rhs.mVal);
        swap(mSize, rhs.mSize);
    }

    T *data() { return mVal; }

    size_t size() const { return mSize; }

private:
    /**
     * The pointer to the array
     */
    T *mVal;
    size_t mSize;
};

//------------------------------------------------------------
// Heap class
//------------------------------------------------------------
class Heap {
public:
    // Constructor
    Heap();

    // This constructor assumes that every element of the array is an
    // element of the heap.
    Heap(Patient *inArray, int inArraySize, int inHeapSize);

    // Accesses an element of the array.
    const Patient &at(int i) const;

    Patient &at(int i);

    /**
     * Returns the index of the left child of the node at index \p i
     * @param i The parent node
     * @return The left child of \p i or -1 if it doesn't have a left child.
     */
    int left(int i) const;

    /**
     * Returns whether the node at index \p i has a left child or not.
     * @param i The parent node.
     * @return Whether it has a left child.
     */
    bool hasLeft(int i) const;

    /**
     * Returns the index of the right child of the node at index \p i
     * @param i The parent node
     * @return The right child of \p i or -1 if it doesn't have a right child.
     */
    int right(int i) const;

    /**
     * Returns whether the node at index \p i has a right child or not.
     * @param i The parent node.
     * @return Whether it has a right child.
     */
    bool hasRight(int i) const;

    /**
     * Returns the index of the parent node of the node at index \p i
     * @param i The child node
     * @return The parent of \p i or -1 if the node doesn't have a parent node.
     */
    int parent(int i) const;

    /**
     * Bubbles down the node at index \p i
     * @param i The node to bubble down
     */
    void maxHeapify(int i);

    /**
     * Builds a max heap such that each node is greater than both its left and right children.
     */
    void buildMaxHeap();

    // Allows comparison between results
    bool operator==(const Heap &rhs);

    bool operator==(const Patient *rhs);

    // Useful for debugging. To use:
    //   Heap h;
    //   cout << h << endl;
    friend std::ostream &operator<<(std::ostream &out, const Heap &h);

    void heapsort();

    Patient extractMax();

    const Patient &max() const;

    Patient &max();

    void insert(Patient patient);

private:
    // The array
    Array<Patient> A;

    // Size of the array
    int arraySize;

    // The number of elements in the heap
    int n;

    void bubbleUp(int i);
};

// Useful for debugging. To use:
//   Heap h;
//   cout << h << endl;
std::string toDot(const Heap &h);
