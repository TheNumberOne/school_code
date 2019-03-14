#pragma once

#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_mat4x4.hpp>
#include <SDL_opengl.h>
#include <glm/gtc/type_ptr.hpp>

template<typename T>
class transformed {
public:
    transformed(T object, const glm::mat4 &transformation) : object(object), transformation(transformation) {}

    void draw() const {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glMultMatrixf(glm::value_ptr(transformation));
        object.draw();
        glPopMatrix();
    }

private:
    T object;
    glm::mat4 transformation;
};

template<typename T>
transformed<T> transform(T object, const glm::mat4 &transformation) {
    return transformed(object, transformation);
}