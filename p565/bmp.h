#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

#include "./Color.h"

typedef int LONG;
typedef unsigned short WORD;
typedef unsigned int DWORD;

#pragma pack(push, 1)
typedef struct tagBITMAPFILEHEADER {
  WORD  bfType;
  DWORD bfSize;
  WORD  bfReserved1;
  WORD  bfReserved2;
  DWORD bfOffBits;
} BITMAPFILEHEADER, *PBITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER {
  // DWORD biSize;
  // LONG  biWidth;
  // LONG  biHeight;
  int biSize;
  short  biWidth;
  short  biHeight;
  WORD  biPlanes;
  WORD  biBitCount;
  DWORD biCompression;
  DWORD biSizeImage;
  LONG  biXPelsPerMeter;
  LONG  biYPelsPerMeter;
  DWORD biClrUsed;
  DWORD biClrImportant;
} BITMAPINFOHEADER, *PBITMAPINFOHEADER;
#pragma pack(pop)

class Bitmap {
 public:
  void read(const std::string& filename);
  void write(const std::string& filename);

  short width() const { return info_header->biWidth; }
  short height() const { return info_header->biHeight; }

  int red(int x, int y) const { return color(x, y, 2); }
  int green(int x, int y) const { return color(x, y, 1); }
  int blue(int x, int y) const { return color(x, y, 0); }
  Color color(int x, int y) const {
    return Color(red(x,y), green(x,y), blue(x,y));
  }
  int gray(int x, int y) const {
    double r = red(x, y) / 255.0;
    double g = green(x, y) / 255.0;
    double b = blue(x, y) / 255.0;
    double linear = 0.2126*r + 0.7152*g + 0.0722*b;
    if (linear <= 0.0031308)
      return (int)(12.92*linear);
    return (int)(255 * (1.055*pow(linear, 1/2.4) - 0.055));
  }
  int quantized(int x, int y, int numBins) const {
    return quantizedColor(gray(x, y), numBins);
  }

  void setRed(int x, int y, int value) { setColor(x, y, 2, value); }
  void setGreen(int x, int y, int value) { setColor(x, y, 1, value); }
  void setBlue(int x, int y, int value) { setColor(x, y, 0, value); }
  void setColor(int x, int y, int r, int g, int b) {
    setRed(x, y, r);
    setGreen(x, y, g);
    setBlue(x, y, b);
  }
  void setColor(int x, int y, int i) {
    setColor(x, y, i, i, i);
  }
  void setColor(int x, int y, Color c) {
    setColor(x, y, c.r, c.g, c.b);
  }

 private:
#define SIZE 3
  int color(int x, int y, int col) const {
    const int idx = offset + (y * row_size + SIZE*x)+col;
    return (unsigned char)(buffer[idx]);
  }

  void setColor(int x, int y, int col, int value) {
    const int idx = offset + (y * row_size + SIZE*x)+col;
    buffer[idx] = (unsigned char)value;
  }


 private:
  std::vector<char> buffer;
  std::streampos length;
  PBITMAPFILEHEADER file_header;
  PBITMAPINFOHEADER info_header;
  size_t offset;
  size_t row_size;
};
