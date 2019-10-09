#define GLM_ENABLE_EXPERIMENTAL

#include "door.h"
#include "sphere.h"
#include "transformed_object.h"
#include "draw_container.h"
#include "display_mesh.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

void door::draw() const {
    _material.load();

    std::vector<glm::vec3> points;

    for (int x = 0; x < 2; x++) {
        for (int y = 0; y < 2; y++) {
            for (int z = 0; z < 2; z++) {
                points.emplace_back(_width * x - _width / 2, _height * y, -_thickness * z);
            }
        }
    }

    std::vector<std::vector<size_t>> shapes{
        {6, 2, 0, 4},
        {3, 7, 5, 1},
        {7, 6, 4, 5},
        {7, 3, 2, 6},
        {2, 3, 1, 0},
        {1, 5, 4, 0}
    };

    std::vector<glm::vec3> normals{
        {0,  0,  1},
        {0,  0,  -1},
        {1,  0,  0},
        {0,  1,  0},
        {-1, 0,  0},
        {0,  -1, 0}
    };

    std::vector<size_t> normal_indices{
        0, 1, 2, 3, 4, 5
    };

    display_mesh(points, shapes, normals, normal_indices);

    auto door_knob = transform(
        multi_transform(
            transform(
                sphere(),
                glm::translate(glm::vec3{0, .4 * _height, _thickness / 2 + .05}) *
                glm::scale(glm::vec3{.05, .05, .05})
            ),
            glm::mat4(1),
            glm::rotate(glm::pi<float>(), glm::vec3{0, 1, 0})
        ),
        glm::translate(glm::vec3{-.4 * _width, 0, -_thickness / 2})
    );
    door_knob.draw();
}

door::door(float width, float height, float thickness) : _width(width), _height(height), _thickness(thickness) {}
