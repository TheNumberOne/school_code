//------------------------------------------------------------
//
// CS 3385
// Project p18
//
// In this project you will be implementing insertion sort
// in C++. The project is called p18 because the algorithm
// you will be implementing is on page 18 of the textbook.
//
// For general project instructions see the "Projects" link
// on the course website.
//
// Un-comment tests one by one in the runTests() function.
// Develop your code in InsertionSort.cpp until it passes
// all tests. See page 18 in the textbook for the algorithm
// you will implement.
//
// You will submit only InsertionSort.cpp and InsertionSort.h.
// Your code will be tested with a slightly modified version
// of this file. Your final score will be solely dependent
// on the number of tests you passed and the quality of your
// code (quality is checked randomly).
//
// *WARNING* Do NOT use any extra libraries. If you do your
// code may not compile and, in any event, you will receive
// a zero for the project. A good way to check that you're not
// using any extra libraries is to make sure that no extra
// #include statements have been added to any of your files.
//
// When you're finished, make sure your code passes all tests.
// Then submit InsertionSort.cpp and InsertionSort.h.
// DO NOT compress them into a zip file -- submit them
// individually. DO NOT submit this file (main.cpp).
// Check InsertionSort.cpp before you submit it to make
// sure it has the modifications you expect. (Sometimes
// people make two copies of a file and submit the wrong
// one.)
//
// Files to submit:
//   * InsertionSort.h
//   * InsertionSort.cpp
// 
//------------------------------------------------------------

#include <iostream>
#include <cstring>

#include "./InsertionSort.h"

using namespace std;

// Macro used for unit tests. Do not modify.
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

  // TODO: Uncomment tests one by one as you develop your implementation
  // of the algorithm.

  // {
  //   int array[] = { 8 };
  //   insertionSort(array, 1);
  //   int result[] = { 8 };
  //   TEST(memcmp(array, result, 1*sizeof(int)) == 0);
  // }

  // {
  //   int array[] = { 1, 4, 2, 3 };
  //   insertionSort(array, 4);
  //   int result[] = { 1, 2, 3, 4 };
  //   TEST(memcmp(array, result, 4*sizeof(int)) == 0);
  // }

  // {
  //   int array[] = { 8, 3, 2, 5, 7, 9, 22, 1, 3 };
  //   insertionSort(array, 9);
  //   int result[] = { 1, 2, 3, 3, 5, 7, 8, 9, 22 };
  //   TEST(memcmp(array, result, 9*sizeof(int)) == 0);
  // }

  // {
  //   int* array = 0;
  //   insertionSort(array, 0);
  //   int* result = 0;
  //   TEST(memcmp(array, result, 0*sizeof(int)) == 0);
  // }

  // Summary of number of tests passed. Do not modify.
  const int numSuccesses = testNum - numFails;
  cout << numSuccesses << "/" << testNum << " tests succeeded" << endl;

  return numFails;
}

int main() {
  // Do not modify.
  return runTests();
}
