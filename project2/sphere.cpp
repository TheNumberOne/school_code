#include <GL/gl.h>
#include <glm/gtc/constants.hpp>
#include <cmath>
#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "sphere.h"
#include "material.hpp"

void sphere::draw() const {
    //.2125	0.1275	0.054	0.714	0.4284	0.18144	0.393548	0.271906	0.166721	0.2
    material material2{
        {.3125, .2275, .054, 1},
        {.714, .4284, .18144, 1},
        {0.393548, 0.271906, 0.166721, 1},
        .2f * 128,
        {0, 0, 0, 1}
    };
    material2.load();
    for (unsigned int i = 0; i < num_strips; i++) {
        glBegin(GL_TRIANGLE_STRIP);
        for (unsigned int j = 0; j <= num_slices; j++) {
            glm::vec3 top = get_point(i + 1, j);
            glm::vec3 bottom = get_point(i, j);
            glNormal3fv(glm::value_ptr(top));
            glVertex3fv(glm::value_ptr(top));
            glNormal3fv(glm::value_ptr(bottom));
            glVertex3fv(glm::value_ptr(bottom));
        }
        glEnd();
    }
}

glm::vec3 sphere::get_point(unsigned int strip, unsigned int slice) const {
    float phi = glm::pi<float>() * strip / num_strips;
    float theta = 2 * glm::pi<float>() * slice / num_slices;

    return {std::sin(phi) * std::cos(theta), std::cos(phi), std::sin(phi) * std::sin(theta)};
}
