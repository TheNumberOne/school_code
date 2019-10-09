//------------------------------------------------------------
// This is a utility class. Usage:
//
//    bit_buffer buf;
//    buf.add(0);
//    buf.add(0);
//    buf.add(1);
//    buf.add(0);
//    cout << buf << endl;
//
//    Output: 0010 in binary (not ASCII)
//
//
//    // Let str be a binary string that looks like 00101100
//    bit_buffer buf(str);
//    while (buf.hasNext()) {
//      cout << (buf.next()?"0":"1");
//    }
//
//    Output: 00101100 in ASCII

//------------------------------------------------------------

#pragma once

#include <vector>
#include <stdexcept>
#include <cmath>

class bit_buffer {
 public:
  bit_buffer() : nbits(0), i(-1) {}
  bit_buffer(std::istream& s) {
    s >> nbits;
    int bytes = (int)ceil(nbits/8.0);
    buf.resize(bytes);
    s.read(buf.data(), bytes);
    i = 7;
    idx = 0;
  }

  void add(int bit) {
    if (bit != 0 && bit != 1) {
      throw std::logic_error("Bad bit");
    }
    if (i < 0) {
      buf.push_back(0);
      i = 7;
    }
    char& c = buf.back();
    c |= (bit << i);
    i--;
    nbits++;
  }

  int numBits() const { return nbits; }

  // Returns the next bit
  int next() {
    int bit = (buf[idx] & (1<<i));
    i--;
    if (i < 0) {
      i = 7;
      idx++;
    }
    return bit;
  }

  bool hasNext() const {
    return idx*8+(7-i) < nbits;
  }

  friend std::ostream& operator<<(std::ostream& out, const bit_buffer& b) {
    out << b.nbits;
    for (int i = 0; i < b.buf.size(); ++i) {
      out << b.buf[i];
    }
    return out;
  }

 private:
  int nbits;
  int i;
  int idx;
  std::vector<char> buf;
};
