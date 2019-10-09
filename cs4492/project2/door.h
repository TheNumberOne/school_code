#pragma once


#include "material.hpp"

class door {
public:
    door(float width, float height, float thickness);

    void draw() const;

private:
    float _width;
    float _height;
    float _thickness;
    material _material{
        {1, 0, 0, 1},
        {1, 0, 0, 1},
        {.1, .1, .1, 1},
        50,
        {0, 0, 0, 0}
    };
};


