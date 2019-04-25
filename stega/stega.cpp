#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "bmp.h"

// Contains the data of the bitmap. The header takes up "offset" number
// of bytes, so the first byte of actual image data is at buffer[offset].
vector<char> buffer;
// Number of pixels in the image. Since the pixels are RGB, there are
// num_pixels * 3 total bytes of image data.
size_t num_pixels;
// The size of the header
size_t offset;

void readBmp(const string& filename);

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: stega filename\n");
    return 1;
  }

  readBmp(argv[1]);

  printf("Successfully read %s. Now print the secret message!\n", argv[1]);

  // TODO: iterate through bytes of data in the image and reconstruct
  // the encoded message.

  // Note: buffer[offset] contains the first byte of data in the image

  return 0;
}

void readBmp(const string& filename) {
  std::ifstream file(filename);

  PBITMAPFILEHEADER file_header;
  PBITMAPINFOHEADER info_header;

  if (file) {
    file.seekg(0,std::ios::end);
    streampos file_length;
    file_length = file.tellg();
    file.seekg(0,std::ios::beg);

    buffer.resize(file_length);
    file.read(&buffer[0], file_length);

    file_header = (PBITMAPFILEHEADER)(&buffer[0]);
    info_header = (PBITMAPINFOHEADER)(&buffer[0] + sizeof(BITMAPFILEHEADER));

    num_pixels = info_header->biWidth * info_header->biHeight;
    offset = sizeof(BITMAPFILEHEADER) + info_header->biSize;
  }
}

