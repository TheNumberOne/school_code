#include <cmath>
#include <glm/geometric.hpp>
#include "slanted_roof.h"
#include "gl_util.h"

slanted_roof::slanted_roof(float _inside_width, float _inside_length, float _slope, float _thickness,
                           float _overhang, material _material, material _material_top)
    : slanted_roof(_inside_width, _inside_length, _slope, _thickness, _overhang, _material,
                   _material_top, false, 0) {}

void slanted_roof::draw() const {
    float roof_angle = std::atan(_slope);
    float roof_underside_height = _inside_length / 2 * _slope; // height not including overhang
    float overhang_height = _overhang * std::sin(roof_angle);
    float overhang_width = _overhang * std::cos(roof_angle);
    float roof_underside_top_y = roof_underside_height;
    float roof_underside_bottom_y = -overhang_height;
    float roof_underside_bottom_z = overhang_width + _inside_length / 2;
    float roof_x = _inside_width / 2 + _overhang;
    float roof_thickness_z = _thickness * std::sin(roof_angle);
    float roof_thickness_y = _thickness * std::cos(roof_angle);
    float roof_top_top_y = roof_underside_top_y + roof_thickness_y;
    float roof_top_bottom_y = roof_underside_bottom_y + roof_thickness_y;
    float roof_top_bottom_z = roof_underside_bottom_z + roof_thickness_z;

    glm::vec3 roof_norm = glm::normalize(glm::vec3{0, roof_thickness_y, roof_thickness_z});

    std::vector<glm::vec3> points{
        // roof underside
        {_slice_right ? _inside_width / 2 + _inside_length / 2 / std::tan(_slice_angle)
                      : roof_x, roof_underside_top_y,    0}, // 0
        {_slice_right ? _inside_width / 2 + (_inside_length + overhang_width) / std::tan(_slice_angle)
                      : roof_x, roof_underside_bottom_y, -roof_underside_bottom_z},
        {-roof_x,               roof_underside_bottom_y, -roof_underside_bottom_z},
        {-roof_x,               roof_underside_top_y,    0},
        {-roof_x,               roof_underside_bottom_y, roof_underside_bottom_z},
        {_slice_right ? _inside_width / 2 - overhang_width / std::tan(_slice_angle)
                      : roof_x, roof_underside_bottom_y, roof_underside_bottom_z},
        // roof topside
        {_slice_right ? _inside_width / 2 + _inside_length / 2 / std::tan(_slice_angle)
                      : roof_x, roof_top_top_y,          0}, //6
        {_slice_right ? _inside_width / 2 +
                        (_inside_length + overhang_width + roof_thickness_z) / std::tan(_slice_angle)
                      : roof_x, roof_top_bottom_y,       -roof_top_bottom_z},
        {-roof_x,               roof_top_bottom_y,       -roof_top_bottom_z},
        {-roof_x,               roof_top_top_y,          0},
        {-roof_x,               roof_top_bottom_y,       roof_top_bottom_z},
        {_slice_right ? _inside_width / 2 - (overhang_width + roof_thickness_z) / std::tan(_slice_angle)
                      : roof_x, roof_top_bottom_y,       roof_top_bottom_z},
    };


    std::vector<std::vector<size_t>> polygons{
        // top of roof
        {6,  9,  10, 11},
        {7,  8,  9,  6},
        //underside of roof
        {5,  4,  3,  0},
        {0,  3,  2,  1},
        // edges of roof
        {6,  11, 5,  0},
        {7,  6,  0,  1},
        {8,  7,  1,  2},
        {9,  8,  2,  3},
        {10, 9,  3,  4},
        {11, 10, 4,  5},
    };

    std::vector<glm::vec3> normals{
        {1,  0,            0}, //right  //0
        {0,  0,            -1},//away  // 1
        {-1, 0,            0}, //left // 2
        {0,  0,            1}, //towards // 3
        {0,  roof_norm.y,  roof_norm.z}, // towards 4
        {0,  roof_norm.y,  -roof_norm.z}, // away 5
        {0,  -roof_norm.y, -roof_norm.z}, // 6
        {0,  -roof_norm.y, roof_norm.z}, // 7
        {0,  -roof_norm.z, roof_norm.y}, // 8
        {0,  -roof_norm.z, -roof_norm.y}, // 9
    };

    std::vector<size_t> normal_indices{
        //top of roof
        4,
        5,
        //under of roof
        6,
        7,
        0,
        0,
        9,
        2,
        2,
        8,
    };

    std::vector<size_t> material_indices{
        //top of roof
        1,
        1,
        //underside of roof
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
    };

    _material.load();
    display_mesh(points, polygons, normals, normal_indices, std::vector{_material, _material_top}, material_indices);
}

slanted_roof::slanted_roof(
    float _inside_width, float _inside_length, float _slope, float _thickness, float _overhang,
    material _material) : slanted_roof(_inside_width, _inside_length, _slope, _thickness, _overhang, _material,
                                       _material) {}

slanted_roof::slanted_roof(float inside_width, float inside_length, float slope, float thickness, float overhang,
                           material material, bool slice_right, float slice_angle) : slanted_roof(inside_width,
                                                                                                  inside_length, slope,
                                                                                                  thickness, overhang,
                                                                                                  material,
                                                                                                  material, slice_right,
                                                                                                  slice_angle) {}

slanted_roof::slanted_roof(float inside_width, float inside_length, float slope, float thickness, float overhang,
                           material material_bottom, material material_top, bool slice_right, float slice_angle)
    : _inside_width(inside_width), _inside_length(inside_length), _slope(slope), _thickness(thickness),
      _overhang(overhang), _material(material_bottom), _material_top(material_top), _slice_right(slice_right),
      _slice_angle(slice_angle) {}
