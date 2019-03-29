#pragma once

#include <memory>

namespace gl {
    class texture {
    public:
        texture(unsigned int slot, const std::string &file);

        texture() = default;

        GLuint name() const { return *i; }

        GLuint slot() const { return _slot; }

        void enable() const;

        void disable() const;

    private:
        GLuint _slot = 0;
        std::shared_ptr<GLuint> i = nullptr;

        void deleteTexture(GLuint *texture);
    };
}
