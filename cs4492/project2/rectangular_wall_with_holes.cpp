
#include <algorithm>
#include "rectangular_wall_with_holes.h"
#include "gl_util.h"
#include "display_mesh.h"
#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>

wall::wall(float inside_height, float outside_height, float width, float thickness, const std::vector<hole> &holes,
           const material &material) : _inside_height_left(inside_height), _inside_height_right(inside_height),
                                       _outside_height_left(outside_height), _outside_height_right(outside_height),
                                       _width(width),
                                       _thickness(thickness), _holes(holes), _material(std::move(material)) {
    std::sort(_holes.begin(), _holes.end(), [](const hole &a, const hole &b) {
        return a.x < b.x;
    });
}


void wall::draw() const {
    float left = -_width / 2;
    float right = _width / 2;

    _material.load();

    std::vector<glm::vec3> normals{
        {0,  0,  1},
        {0,  0,  -1},
        {-1, 0,  0},
        {1,  0,  0},
        {0,  1,  0},
        {0,  -1, 0}
    };

    float current_left = left;
    for (const auto &hole: _holes) {
        // Add shape to current_left
        float hole_left = hole.x - hole.width / 2;
        float hole_right = hole.x + hole.width / 2;
        float hole_top = hole.y + hole.height / 2;
        float hole_bottom = hole.y - hole.height / 2;

        std::vector<glm::vec3> points{
            {current_left, inside_height(current_left),  0},
            {current_left, 0,                            0},
            {hole_left,    inside_height(hole_left),     0},
            {hole_left,    hole_top,                     0},
            {hole_left,    hole_bottom,                  0},
            {hole_left,    0,                            0},
            {hole_right,   inside_height(hole_right),    0},
            {hole_right,   hole_top,                     0},
            {hole_right,   hole_bottom,                  0},
            {hole_right,   0,                            0},
            {current_left, outside_height(current_left), -_thickness},
            {current_left, 0,                            -_thickness},
            {hole_left,    outside_height(hole_left),    -_thickness},
            {hole_left,    hole_top,                     -_thickness},
            {hole_left,    hole_bottom,                  -_thickness},
            {hole_left,    0,                            -_thickness},
            {hole_right,   outside_height(hole_right),   -_thickness},
            {hole_right,   hole_top,                     -_thickness},
            {hole_right,   hole_bottom,                  -_thickness},
            {hole_right,   0,                            -_thickness},
        };

        std::vector<std::vector<size_t>> shapes{
            {2,  0,  1,  5},
            {6,  2,  3,  7},
            {8,  4,  5,  9},
            {10, 12, 15, 11},
            {12, 16, 17, 13},
            {14, 18, 19, 15},
            {7,  17, 18, 8},
            {7,  3,  13, 17},
            {13, 3,  4,  14},
            {18, 14, 4,  8}
        };

        std::vector<size_t> normal_indices{
            0,
            0,
            0,
            1,
            1,
            1,
            2,
            5,
            3,
            4
        };

        display_mesh(points, shapes, normals, normal_indices);
        current_left = hole_right;
    }

    std::vector<glm::vec3> points{};

    for (auto l : {left, current_left, right}) {
        points.emplace_back(l, inside_height(l), 0);
        points.emplace_back(l, outside_height(l), -_thickness);
        points.emplace_back(l, 0, -_thickness);
        points.emplace_back(l, 0, 0);
    }
    std::vector<std::vector<size_t >> shapes{
        {8, 4,  7,  11},
        {5, 9,  10, 6},
        {9, 8,  11, 10},
        {9, 1,  0,  8},
        {0, 1,  2,  3},
        {2, 10, 11, 3}
    };
    std::vector<size_t> normal_indices{
        0,
        1,
        3,
        4,
        2,
        5
    };
    display_mesh(points, shapes, normals, normal_indices);
}

wall::wall(float inside_height_left, float outside_height_left, float inside_height_right,
           float outside_height_right, float width, float thickness, const std::vector<hole> &_holes,
           const material &_material) : _inside_height_left(inside_height_left),
                                        _outside_height_left(outside_height_left),
                                        _inside_height_right(inside_height_right),
                                        _outside_height_right(outside_height_right), _width(width),
                                        _thickness(thickness), _holes(_holes), _material(_material) {}

float wall::inside_height(float x) const {
    return (x + _width / 2) / _width * (_inside_height_right - _inside_height_left) + _inside_height_left;
}

float wall::outside_height(float x) const {
    return (x + _width / 2) / _width * (_outside_height_right - _outside_height_left) + _outside_height_left;
}

hole::hole(float width, float height, float x, float y) : width(width), height(height), x(x), y(y) {}
