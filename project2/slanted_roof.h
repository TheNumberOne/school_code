#pragma once


#include "material.hpp"

class slanted_roof {
public:
    slanted_roof(float _inside_width, float _inside_length, float _slope, float _thickness,
                 float _overhang, material _material, material _material_top);

    slanted_roof(float inside_width, float inside_length, float slope, float thickness, float overhang,
                 material material_bottom, material material_top, bool slice_right, float slice_angle);

    slanted_roof(float _inside_width, float _inside_length, float _slope, float _thickness,
                 float _overhang, material _material);

    slanted_roof(float inside_width, float inside_length, float slope, float thickness, float overhang,
                 material material, bool slice_right, float slice_angle);

    void draw() const;

private:
    float _inside_width;  // x axis
    float _inside_length; // z axis
    float _slope;
    float _thickness;
    float _overhang;
    material _material;
    material _material_top;
    bool _slice_right = false;
    float _slice_angle;
};


