#pragma once

#include <vector>
#include "material.hpp"

struct hole {
    hole(float width, float height, float x, float y);

    float width;
    float height;
    float x;
    float y;
};

class wall {
public:
    wall(float inside_height, float outside_height, float width, float thickness, const std::vector<hole> &holes,
         const material &material);

    wall(float inside_height_left, float outside_height_left, float inside_height_right, float outside_height_right,
         float width, float thickness, const std::vector<hole> &_holes, const material &_material);

    void draw() const;

private:
    float _inside_height_left;
    float _outside_height_left;
    float _inside_height_right;
    float _outside_height_right;
    float _width;
    float _thickness;
    std::vector<hole> _holes;
    material _material;

    float inside_height(float x) const;

    float outside_height(float x) const;
};