
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include "rectangular_wall_with_holes.h"
#include <algorithm>


gl::buffer::buffer() {
    glGenBuffers(1, &i);
}

gl::buffer::~buffer() {
    if (i != 0) glDeleteBuffers(1, &i);
}

gl::buffer::buffer(gl::buffer &&other) noexcept {
    std::swap(i, other.i);
}

gl::buffer &gl::buffer::operator=(gl::buffer &&other) noexcept {
    std::swap(i, other.i);
    return *this;
}

