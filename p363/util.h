#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <regex>
#include <iterator>

#define TEST(test) { \
  testNum++; \
  if (!(test)) { \
    cerr << "Test " << testNum << " failed" << endl; \
    numFails++; \
  } \
}

template <typename T>
void printArray(const T* A, int n) {
  using namespace std;
  for (int i = 0; i < n; ++i) {
    cout << A[i] << endl;
  }
  cout << endl;
}

template <typename T>
bool arrayEquals(const T* A, const T* B, int n) {
  for (int i = 0; i < n; ++i) {
    if (A[i] != B[i]) return false;
  }
  return true;
}

