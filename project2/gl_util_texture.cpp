
#include <algorithm>
#include "rectangular_wall_with_holes.h"
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include "gl_util_texture.h"
#include "stb_image.h"

void gl::texture::deleteTexture(GLuint *texture) {
    glActiveTexture(GL_TEXTURE0 + _slot);
    glDeleteTextures(1, texture);
    free(texture);
}

gl::texture::texture(unsigned int slot, const std::string &file) : _slot(slot),
                                                                   i(new GLuint(0), [&](auto i) { deleteTexture(i); }) {
    int width, height, channels;
    unsigned char *raster = stbi_load(file.c_str(), &width, &height, &channels, 4);
    glActiveTexture(GL_TEXTURE0 + slot);
    glGenTextures(1, i.get());
    glBindTexture(GL_TEXTURE_2D, *i);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, raster);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
}

void gl::texture::enable() const {
    glEnable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0 + _slot);
    glBindTexture(GL_TEXTURE_2D, *i);
}

void gl::texture::disable() const {
    glDisable(GL_TEXTURE_2D);
}