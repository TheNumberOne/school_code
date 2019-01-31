//------------------------------------------------------------
//
// CS 3385
// Project p72
//
// In this project you will be implementing max subarray.
//
// You are responsible for adding declarations of your
// functions to MaxSubarray.h.
//
// Do not use any extra libraries. See comments to header
// file includes in MaxSubarray.h and MaxSubarray.cpp.
//
// Files to submit:
//   * MaxSubarray.h
//   * MaxSubarray.cpp
// 
//------------------------------------------------------------

#include <iostream>

#include "./MaxSubarray.h"

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

   {
     //          0   1   2*  3  4   5
     int A[] = { 1, -4, 14, -2, 3, -1 };
     Result r = findMaxCrossingSubarray(A, 0, 2, 5);
     Result c(2, 4, 15);
     TEST(r == c);
   }

   {
     //          0  1   2  3*  4   5  6
     int A[] = { 0, 5, -4, 1, -2, -3, 6 };
     Result r = findMaxCrossingSubarray(A, 0, 3, 6);
     Result c(1, 6, 3);
     TEST(r == c);
   }

   {
     //          0  1   2  3*  4   5  6
     int A[] = { 0, 5, -4, 1, -2, -3, 5 };
     Result r = findMaxCrossingSubarray(A, 0, 3, 6);
     Result c(1, 6, 2);
     TEST(r == c);
   }

   {
     int A[] = { 13, -3, 4 };
     Result r = findMaxSubarray(A, 0, 2);
     Result c(0, 2, 14);
     TEST(r == c);
   }

   {
     int A[] = { 13, 4, -3 };
     Result r = findMaxSubarray(A, 0, 2);
     Result c(0, 1, 17);
     TEST(r == c);
   }

   {
     int A[] = { -3, 4, 13 };
     Result r = findMaxSubarray(A, 0, 2);
     Result c(1, 2, 17);
     TEST(r == c);
   }

   {
     int A[] = { 4, -3, 13 };
     Result r = findMaxSubarray(A, 0, 2);
     Result c(0, 2, 14);
     TEST(r == c);
   }

   {
     int A[] = { 4, -3, -13, 5, 3 };
     Result r = findMaxSubarray(A, 0, 4);
     Result c(3, 4, 8);
     TEST(r == c);
   }

   {
     int A[] = { 4, 3, -13, -5, 3 };
     Result r = findMaxSubarray(A, 0, 4);
     Result c(0, 1, 7);
     TEST(r == c);
   }

   {
     int A[] = { -4, 4, -3, 5, -3 };
     Result r = findMaxSubarray(A, 0, 4);
     Result c(1, 3, 6);
     TEST(r == c);
   }

   {
     int A[] = { 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };
     Result r = findMaxSubarray(A, 0, 15);
     Result c(7, 10, 43);
     TEST(r == c);
   }


  const int numSuccesses = testNum - numFails;
  cout << numSuccesses << "/" << testNum << " tests succeeded" << endl;

  return numFails;
}

int main() {
  // TODO: Add test code as necessary.
  // This file will NOT be submitted, though!

  return runTests();
}
