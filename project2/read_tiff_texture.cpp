
#include <tiffio.h>
#include <stdexcept>
#include <bits/unique_ptr.h>
#include <GLES2/gl2.h>
#include "read_tiff_texture.h"

GLuint read_tiff_texture(const char *path) {
    auto tiff = std::unique_ptr<TIFF, decltype(&TIFFClose)>{
        TIFFOpen("assets/TexturesCom_BrickPavement_1.5x1.5_512_albedo.tif", "r"), &TIFFClose
    };

    if (!tiff) throw std::runtime_error("Unable to open tiff");

    uint32 width, length;
    TIFFGetField(tiff.get(), TIFFTAG_IMAGEWIDTH, &width);
    TIFFGetField(tiff.get(), TIFFTAG_IMAGELENGTH, &length);

    size_t pixels = width * length;
    auto raster = std::unique_ptr<uint32, decltype(&_TIFFfree)>(
        static_cast<uint32 *>(_TIFFmalloc(pixels * sizeof(uint32))),
        &_TIFFfree
    );

    TIFFReadRGBAImage(tiff.get(), width, length, raster.get(), 0);
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, length, 0, GL_RGBA, GL_UNSIGNED_BYTE, raster.get());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
    return texture;
}
