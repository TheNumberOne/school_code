#include <iostream>
#include <fstream>
#include <vector>
#include <string>

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

void readBmp(const string &filename);

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Usage: stega filename\n");
        return 1;
    }
    
    readBmp(argv[1]);
    
    printf("Successfully read %s. Now print the secret message!\n", argv[1]);
    
    // TODO: iterate through bytes of data in the image and reconstruct
    // the encoded message.
    
    std::string message(num_pixels * 3 / 8, '\0');
    char *i = &message[0];
    auto *start = (uint8_t *) (buffer.data() + offset);
    uint8_t *end = start + num_pixels * 3;
    
    for (auto p = (uint64_t *) start; (uint8_t *) (p + 1) <= end; p++) {
        // extract least significant bits
        uint64_t m = *p & 0x0101010101010101uL;
        // squash the bits together
        uint64_t a = m | (m >> 7u);
        uint64_t b = a | (a >> 14u);
        uint8_t c = b | (b >> 28u);
        if (!c) break;
        *(i++) = c;
    }
    message.resize(i - message.data());
    std::cout << message << std::endl;
    
    return 0;
}

void readBmp(const string &filename)
{
    std::ifstream file(filename);
    
    PBITMAPFILEHEADER file_header;
    PBITMAPINFOHEADER info_header;
    
    if (file) {
        file.seekg(0, std::ios::end);
        streampos file_length;
        file_length = file.tellg();
        file.seekg(0, std::ios::beg);
        
        buffer.resize(file_length);
        file.read(&buffer[0], file_length);
        
        file_header = (PBITMAPFILEHEADER) (&buffer[0]);
        info_header = (PBITMAPINFOHEADER) (&buffer[0] + sizeof(BITMAPFILEHEADER));
        
        num_pixels = info_header->biWidth * info_header->biHeight;
        offset = sizeof(BITMAPFILEHEADER) + info_header->biSize;
    }
}

