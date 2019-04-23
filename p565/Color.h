#pragma once

struct Color {
  Color(int r_, int g_, int b_) 
      : r(r_), g(g_), b(b_) {
  }
  static Color createRandom(int seed) {
    srand(seed);
    return Color(rand() % 256, rand() % 256, rand() % 256);
  }
  int r, g, b;
};

inline int quantizedColor(int gray, int numBins) {
  return (int)((((int)((gray / 256.0) * numBins)) / (double)numBins) * 256);
}
