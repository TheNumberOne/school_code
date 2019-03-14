#include <cmath>
#include <glm/geometric.hpp>
#include "slanted_roof.h"
#include "gl_util.h"

slanted_roof::slanted_roof(float _inside_width, float _inside_length, float _slope, float _thickness,
                           float _overhang, material _material, material _material_top)
    : _inside_width(_inside_width), _inside_length(_inside_length), _slope(_slope), _thickness(_thickness),
      _overhang(_overhang), _material(_material), _material_top(_material_top) {}

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
        {roof_x,  roof_underside_top_y,    0}, // 0
        {roof_x,  roof_underside_bottom_y, -roof_underside_bottom_z},
        {-roof_x, roof_underside_bottom_y, -roof_underside_bottom_z},
        {-roof_x, roof_underside_top_y,    0},
        {-roof_x, roof_underside_bottom_y, roof_underside_bottom_z},
        {roof_x,  roof_underside_bottom_y, roof_underside_bottom_z},
        // roof topside
        {roof_x,  roof_top_top_y,          0}, //6
        {roof_x,  roof_top_bottom_y,       -roof_top_bottom_z},
        {-roof_x, roof_top_bottom_y,       -roof_top_bottom_z},
        {-roof_x, roof_top_top_y,          0},
        {-roof_x, roof_top_bottom_y,       roof_top_bottom_z},
        {roof_x,  roof_top_bottom_y,       roof_top_bottom_z},
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
