//------------------------------------------------------------
//
// CS 3385
// Project p34
//
// In this project you will be implementing merge sort.
//
// You will implement three functions: merge() (p. 31),
// mergeSortImpl() (it's called Merge-Sort() on p. 34),
// and mergeSort(), which is a function which will simply
// call mergeSortImpl(). Having a separate mergeSort()
// function makes a cleaner interface for users to call
// your function.
//
// You are responsible for adding declarations of your
// functions to MergeSort.h. See InsertionSort.h in 
// project p18 for an example of how to do this.
//
// Do not use any extra libraries.
//
// When you're finished, make sure your code passes all tests.
// Then submit MergeSort.cpp and MergeSort.h.
// DO NOT compress them into a zip file -- submit them
// individually. DO NOT submit this file (main.cpp).
// Check MergeSort.cpp before you submit it to make
// sure it has the modifications you expect. (Sometimes
// people make two copies of a file and submit the wrong
// one.)
//
// Files to submit:
//   * MergeSort.h
//   * MergeSort.cpp
// 
//------------------------------------------------------------

#include <iostream>
#include <cstring>

#include "./MergeSort.h"

using namespace std;

#define TEST(test) { \
  testNum++; \
  if (!(test)) { \
    cerr << "Test " << testNum << " failed" << endl; \
    numFails++; \
  } \
}

int runTests() {
  int numFails = 0;
  int testNum = 0;

  // Note: Array values in testing will not be greater than 100.

  {
    int array[] = { 1, 4, 2, 3 };
    merge(array, 0, 1, 3);
    int result[] = { 1, 2, 3, 4 };
    TEST(memcmp(array, result, 4*sizeof(int)) == 0);
  }

  {
    int array[] = { 1, 8, 2, 3 };
    merge(array, 0, 1, 3);
    int result[] = { 1, 2, 3, 8 };
    TEST(memcmp(array, result, 4*sizeof(int)) == 0);
  }

  {
    int array[] = { 1, 18, 19, 3, 12, 15 };
    merge(array, 0, 2, 5);
    int result[] = { 1, 3, 12, 15, 18, 19 };
    TEST(memcmp(array, result, 6*sizeof(int)) == 0);
  }

  {
    int array[] = { 1, 18, 3, 12, 15, 19 };
    merge(array, 0, 1, 5);
    int result[] = { 1, 3, 12, 15, 18, 19 };
    TEST(memcmp(array, result, 6*sizeof(int)) == 0);
  }

  {
    int array[] = { 1, 3, 12, 18, 19, 15 };
    merge(array, 0, 4, 5);
    int result[] = { 1, 3, 12, 15, 18, 19 };
    TEST(memcmp(array, result, 6*sizeof(int)) == 0);
  }

  {
    int array[] = { 19, 3, 12, 18, 1, 15 };
    mergeSortImpl(array, 0, 5);
    int result[] = { 1, 3, 12, 15, 18, 19 };
    TEST(memcmp(array, result, 6*sizeof(int)) == 0);
  }

  {
    int array[] = { 19, 3, 12, 18, 1, 15 };
    mergeSortImpl(array, 0, 4);
    int result[] = { 1, 3, 12, 18, 19, 15 };
    TEST(memcmp(array, result, 6*sizeof(int)) == 0);
  }

  {
    int array[] = { 19, 3, 12, 18, 1, 15 };
    mergeSortImpl(array, 1, 4);
    int result[] = { 19, 1, 3, 12, 18, 15 };
    TEST(memcmp(array, result, 6*sizeof(int)) == 0);
  }

  {
    int array[] = { 19, 3, 12, 18, 1, 15 };
    mergeSort(array, 6);
    int result[] = { 1, 3, 12, 15, 18, 19 };
    TEST(memcmp(array, result, 6*sizeof(int)) == 0);
  }

  {
    int array[] = { 8, 3, -1, 12, 3, 15, 4 };
    mergeSort(array, 6);
    int result[] = { -1, 3, 3, 8, 12, 15, 4 };
    TEST(memcmp(array, result, 7*sizeof(int)) == 0);
  }

  {
    int array[] = { 8, 3, -1, 12, 3, 15, 4 };
    mergeSort(array, 7);
    int result[] = { -1, 3, 3, 4, 8, 12, 15 };
    TEST(memcmp(array, result, 7*sizeof(int)) == 0);
  }

    {
        int array[] = {};
        mergeSort(array, 0);
        int result[] = {};
        TEST(memcmp(array, result, 0* sizeof(int)) == 0);
    }

  const int numSuccesses = testNum - numFails;
  cout << numSuccesses << "/" << testNum << " tests succeeded" << endl;

  return numFails;
}

int main() {
  return runTests();
}
