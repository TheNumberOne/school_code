#pragma once

// Provides I/O
#include <iostream>
// Provides size_t
#include <cstdlib>
// Provides INT_MAX and INT_MIN
// You can consider INT_MIN to be negative infinity
// and INT_MAX to be infinity
#include <climits>

// This is the struct you will return from your functions.
struct Result {
  // Constructor
  Result(int left_, int right_, int sum_)
      : left(left_), right(right_), sum(sum_) {}

  // Allows comparison between results
  bool operator==(const Result& rhs) {
    return left == rhs.left && right == rhs.right && sum == rhs.sum;
  }

  // Useful for debugging. To use:
  //   Result r(x, y, z);
  //   cout << r << endl;
  friend std::ostream& operator<<(std::ostream& out, const Result& r) {
    out << r.left << " " << r.right << " " << r.sum;
    return out;
  }
  
  // The data members
  int left, right, sum;
};

