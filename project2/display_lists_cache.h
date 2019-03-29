#pragma once

#include <GL/glew.h>

class display_lists_cache {
public:
    template<typename T>
    explicit display_lists_cache(const T &to_cache) {
        list = glGenLists(1);
        glNewList(list, GL_COMPILE);
        try {
            to_cache.draw();
        } catch (...) {
            glEndList();
            glDeleteLists(list, 1);
            throw;
        }
        glEndList();
    }

    display_lists_cache() = default;

    display_lists_cache(display_lists_cache &&other) noexcept;

    display_lists_cache &operator=(display_lists_cache &&other) noexcept;

    display_lists_cache(const display_lists_cache &) = delete;

    auto operator=(const display_lists_cache &) = delete;

    ~display_lists_cache() {
        glDeleteLists(list, 1);
    }

    void draw() const {
        glCallList(list);
    }

private:
    GLuint list = 0;
};


display_lists_cache::display_lists_cache(display_lists_cache &&other) noexcept {
    std::swap(list, other.list);
}

display_lists_cache &display_lists_cache::operator=(display_lists_cache &&other) noexcept {
    std::swap(list, other.list);
    return *this;
}


