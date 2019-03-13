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

    void draw();

private:
    float _inside_height;
    float _outside_height;
    float _width;
    float _thickness;
    std::vector<hole> _holes;
    material _material;
};