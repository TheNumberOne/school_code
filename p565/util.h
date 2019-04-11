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

std::string removeWhitespace(const std::string& s) {
  using namespace std;
  regex e("\\s");
  string s2;
  regex_replace(back_inserter(s2), s.begin(), s.end(), e, "");
  return s2;
}

bool stringEquals(const std::string& a, const std::string& b) {
  return removeWhitespace(a) == removeWhitespace(b);
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

