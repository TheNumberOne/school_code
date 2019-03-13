
#include <glm/gtc/type_ptr.hpp>
#include "rectangular_wall_with_holes.h"
#include <algorithm>
#include <GL/glew.h>
#include "gl_util.h"


void display_mesh(const std::vector<glm::vec3> &points, const std::vector<std::vector<size_t>> &shapes,
                  const std::vector<glm::vec3> &normals, const std::vector<size_t> &normal_indices) {
    for (size_t i = 0; i < shapes.size(); i++) {
        const auto &polygon = shapes[i];
        glNormal3fv(glm::value_ptr(normals[normal_indices[i]]));
        glBegin(GL_POLYGON);
        for (auto index : polygon) {
            glVertex3fv(glm::value_ptr(points[index]));
        }
        glEnd();
    }
}
