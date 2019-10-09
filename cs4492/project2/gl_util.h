#pragma once

#include <GL/glew.h>
#include <GL/gl.h>
#include <vector>
#include <string>
#include "material.hpp"

namespace gl {
    class buffer {
    public:
        buffer();

        struct no_init {
        };

        buffer(no_init) {}

        ~buffer();

        buffer(const buffer &) = delete;

        buffer &operator=(const buffer &) = delete;

        buffer(buffer &&) noexcept;

        buffer &operator=(buffer &&) noexcept;

        GLuint name() { return i; }

    private:
        GLuint i = 0;
    };
}