#pragma once


#include "material.hpp"

class slanted_roof {
public:
    slanted_roof(float _inside_width, float _inside_length, float _slope, float _thickness,
                 float _overhang, material _material, material _material_top);

    void draw() const;

private:
    float _inside_width;  // x axis
    float _inside_length; // z axis
    float _slope;
    float _thickness;
    float _overhang;
    material _material;
    material _material_top;
};


