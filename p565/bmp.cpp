#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "bmp.h"

void Bitmap::read(const string& filename) {
  std::ifstream file(filename, ios::binary);

  if (file) {
    file.seekg(0,std::ios::end);
    length = file.tellg();
    file.seekg(0,std::ios::beg);

    buffer.resize(length);
    file.read(&buffer[0],length);

    file_header = (PBITMAPFILEHEADER)(&buffer[0]);
    info_header =
        (PBITMAPINFOHEADER)(&buffer[0] + sizeof(BITMAPFILEHEADER));

    offset = file_header->bfOffBits;
    row_size =
        ((int)((info_header->biBitCount*info_header->biWidth+31)/32.0))*4;

    // cout << buffer[0] << buffer[1] << endl;
    // cout << "file_header type = " << file_header->bfType << endl;
    // cout << "file_header size = " << file_header->bfSize << endl;
    // cout << "file_header off = " << file_header->bfOffBits << endl;
    // cout << "dims = " << info_header->biWidth << " " << info_header->biHeight
    //      << endl;
    // cout << "color planes = " << info_header->biPlanes << endl;
    // cout << "bit count = " << info_header->biBitCount << endl;
  }
}

void Bitmap::write(const string& filename) {
  std::ofstream file(filename, ios::binary);
  if (file) {
    file.write(&buffer[0], length);
  }
}
