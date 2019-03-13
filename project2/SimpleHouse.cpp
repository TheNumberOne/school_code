#include <glm/vec3.hpp>
#include <vector>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include "SimpleHouse.hpp"
#include "material.hpp"

void SimpleHouse::draw() {
    float roof_pitch = 3.f / 12.f; // low pitch according to http://www.dimensionsinfo.com/dimensions-of-a-roof/
    float roof_angle = std::atan(roof_pitch);
    float overhang_length = 1; // using meters here.
    float roof_thickness = .3;
    float wall_thickness = .15;
    float height = 3; // Height of walls.
    float door_height = 2.5;
    float door_width = 1.5;
    float door_center_offset_x_frac = .75;
    float window_width = 2;
    float window_height = 1.5f;
    float window_1_center_offset_x_frac = .25;
    float window_2_center_offset_x_frac = .5;
    float window_base_offset_y = 1;
    float width = 20; // Inside _width
    float length = 13; // Inside length

    float walls_inside_x = width / 2;
    float walls_outside_x = walls_inside_x + wall_thickness;
    float walls_inside_z = length / 2;
    float walls_outside_z = walls_inside_z + wall_thickness;
    float walls_inside_y = wall_thickness * roof_pitch + height;
    float walls_outside_y = height;

    float roof_underside_height = walls_inside_z * roof_pitch; // height not including overhang
    float overhang_height = overhang_length * std::sin(roof_angle);
    float overhang_width = overhang_length * std::cos(roof_angle);
    float roof_underside_top_y = roof_underside_height + height;
    float roof_underside_bottom_y = height - overhang_height;
    float roof_underside_bottom_z = walls_outside_z + overhang_width;
    float roof_x = walls_outside_x + overhang_length;
    float roof_thickness_z = roof_thickness * std::sin(roof_angle);
    float roof_thickness_y = roof_thickness * std::cos(roof_angle);
    float roof_top_top_y = roof_underside_top_y + roof_thickness_y;
    float roof_top_bottom_y = roof_underside_bottom_y + roof_thickness_y;
    float roof_top_bottom_z = roof_underside_bottom_z + roof_thickness_z;

    glm::vec3 roof_norm = glm::normalize(glm::vec3{0, roof_thickness_y, roof_thickness_z});

    float door_left_x = width * door_center_offset_x_frac - walls_inside_x - door_width / 2;
    float door_right_x = door_left_x + door_width;

    float window1_left_x = width * window_1_center_offset_x_frac - walls_inside_x - window_width / 2;
    float window1_right_x = window1_left_x + window_width;
    float window1_bottom_y = window_base_offset_y;
    float window1_top_y = window1_bottom_y + window_height;

    float window2_left_x = width * window_2_center_offset_x_frac - walls_inside_x - window_width / 2;
    float window2_right_x = window2_left_x + window_width;
    float window2_bottom_y = window_base_offset_y;
    float window2_top_y = window2_bottom_y + window_height;

    std::vector<glm::vec3> points{
        // Wall bases inside
        {walls_inside_x,   0,                       -walls_inside_z}, // 0
        {-walls_inside_x,  0,                       -walls_inside_z},
        {-walls_inside_x,  0,                       walls_inside_z},
        {walls_inside_x,   0,                       walls_inside_z},
        //Wall bases outside
        {walls_outside_x,  0,                       -walls_outside_z}, // 4
        {-walls_outside_x, 0,                       -walls_outside_z},
        {-walls_outside_x, 0,                       walls_outside_z},
        {walls_outside_x,  0,                       walls_outside_z},
        //Wall tops inside
        {walls_inside_x,   walls_inside_y,          -walls_inside_z}, // 8
        {-walls_inside_x,  walls_inside_y,          -walls_inside_z},
        {-walls_inside_x,  walls_inside_y,          walls_inside_z},
        {walls_inside_x,   walls_inside_y,          walls_inside_z},
        //Wall tops outside
        {walls_outside_x,  walls_outside_y,         -walls_outside_z}, // 12
        {-walls_outside_x, walls_outside_y,         -walls_outside_z},
        {-walls_outside_x, walls_outside_y,         walls_outside_z},
        {walls_outside_x,  walls_outside_y,         walls_outside_z},
        // Roof underside meets wall inside
        {walls_inside_x,   roof_underside_top_y,    0}, // 16
        {-walls_inside_x,  roof_underside_top_y,    0},
        // meets wall outside
        {walls_outside_x,  roof_underside_top_y,    0}, //18
        {-walls_outside_x, roof_underside_top_y,    0},
        // roof underside
        {roof_x,           roof_underside_top_y,    0}, // 20
        {roof_x,           roof_underside_bottom_y, -roof_underside_bottom_z},
        {-roof_x,          roof_underside_bottom_y, -roof_underside_bottom_z},
        {-roof_x,          roof_underside_top_y,    0},
        {-roof_x,          roof_underside_bottom_y, roof_underside_bottom_z},
        {roof_x,           roof_underside_bottom_y, roof_underside_bottom_z},
        // roof topside
        {roof_x,           roof_top_top_y,          0}, //26
        {roof_x,           roof_top_bottom_y,       -roof_top_bottom_z},
        {-roof_x,          roof_top_bottom_y,       -roof_top_bottom_z},
        {-roof_x,          roof_top_top_y,          0},
        {-roof_x,          roof_top_bottom_y,       roof_top_bottom_z},
        {roof_x,           roof_top_bottom_y,       roof_top_bottom_z},
        // door inside
        {door_right_x,     door_height,             walls_inside_z}, //32
        {door_right_x,     walls_inside_y,          walls_inside_z},
        {door_left_x,      walls_inside_y,          walls_inside_z},
        {door_left_x,      door_height,             walls_inside_z},
        {door_left_x,      0,                       walls_inside_z},
        {door_right_x,     0,                       walls_inside_z},
        //door outside
        {door_right_x,     door_height,             walls_outside_z}, //38
        {door_right_x,     walls_outside_y,         walls_outside_z},
        {door_left_x,      walls_outside_y,         walls_outside_z},
        {door_left_x,      door_height,             walls_outside_z},
        {door_left_x,      0,                       walls_outside_z},
        {door_right_x,     0,                       walls_outside_z},
        //window 1 inside
        {window1_right_x,  window1_top_y,           walls_inside_z}, //44
        {window1_right_x,  walls_inside_y,          walls_inside_z},
        {window1_left_x,   walls_inside_y,          walls_inside_z},
        {window1_left_x,   window1_top_y,           walls_inside_z},
        {window1_left_x,   window1_bottom_y,        walls_inside_z},
        {window1_left_x,   0,                       walls_inside_z},
        {window1_right_x,  0,                       walls_inside_z},
        {window1_right_x,  window1_bottom_y,        walls_inside_z},
        //window 1 outside
        {window1_right_x,  window1_top_y,           walls_outside_z}, //52
        {window1_right_x,  walls_outside_y,         walls_outside_z},
        {window1_left_x,   walls_outside_y,         walls_outside_z},
        {window1_left_x,   window1_top_y,           walls_outside_z},
        {window1_left_x,   window1_bottom_y,        walls_outside_z},
        {window1_left_x,   0,                       walls_outside_z},
        {window1_right_x,  0,                       walls_outside_z},
        {window1_right_x,  window1_bottom_y,        walls_outside_z},
        //window 2 inside
        {window2_right_x,  window2_top_y,           walls_inside_z}, //60
        {window2_right_x,  walls_inside_y,          walls_inside_z},
        {window2_left_x,   walls_inside_y,          walls_inside_z},
        {window2_left_x,   window2_top_y,           walls_inside_z},
        {window2_left_x,   window2_bottom_y,        walls_inside_z},
        {window2_left_x,   0,                       walls_inside_z},
        {window2_right_x,  0,                       walls_inside_z},
        {window2_right_x,  window2_bottom_y,        walls_inside_z},
        //window 2 outside
        {window2_right_x,  window2_top_y,           walls_outside_z}, //68
        {window2_right_x,  walls_outside_y,         walls_outside_z},
        {window2_left_x,   walls_outside_y,         walls_outside_z},
        {window2_left_x,   window2_top_y,           walls_outside_z},
        {window2_left_x,   window2_bottom_y,        walls_outside_z},
        {window2_left_x,   0,                       walls_outside_z},
        {window2_right_x,  0,                       walls_outside_z},
        {window2_right_x,  window2_bottom_y,        walls_outside_z},
    };


    std::vector<std::vector<size_t>> polygons{
        // Inside walls
        {11, 16, 8,  0,  3},
        {8,  9,  1,  0},
        {9,  17, 10, 2,  1},
        //forward wall
        {10, 46, 47, 48, 49, 2},
        {46, 45, 44, 47},
        {48, 51, 50, 49},
        {45, 62, 63, 63, 65, 50, 51, 44},
        {62, 61, 60, 63},
        {64, 67, 66, 65},
        {61, 34, 35, 36, 66, 67, 60},
        {34, 33, 32, 35},
        {33, 11, 3,  37, 32},

        // outside walls
        {12, 18, 15, 7,  4},
        {13, 12, 4,  5},
        {14, 19, 13, 5,  6},
        //forward wall
        {54, 14, 6,  57, 56, 55},
        {53, 54, 55, 52},
        {59, 56, 57, 58},
        {70, 53, 52, 59, 58, 73, 72, 71},
        {69, 70, 71, 68},
        {75, 72, 73, 74},
        {40, 69, 68, 75, 74, 42, 41},
        {39, 40, 41, 38},
        {15, 39, 37, 43, 7},

        // top of roof
        {26, 29, 30, 31},
        {27, 28, 29, 26},
        //underside of roof
        {25, 24, 23, 20},
        {20, 23, 22, 21},
        // edges of roof
        {26, 31, 25, 20},
        {27, 26, 20, 21},
        {28, 27, 21, 22},
        {29, 28, 22, 23},
        {30, 29, 23, 24},
        {31, 30, 24, 25},
        // door frame
        {38, 32, 37, 43},
        {38, 41, 35, 32},
        {35, 41, 42, 36},
        //window 1 frame
        {52, 44, 51, 59},
        {52, 55, 47, 44},
        {47, 55, 56, 48},
        {51, 48, 56, 59},
        //window 2 frame
        {68, 60, 67, 75},
        {68, 71, 63, 60},
        {63, 71, 72, 64},
        {67, 64, 72, 75},
    };

    std::vector<glm::vec3> normals{
        {1, 0, 0}, //right
        {0, 0, -1},//away
        {-1, 0, 0}, //left
        {0, 0, 1}, //towards
        roof_norm, //back roof out
        -roof_norm, //back roof in
        glm::reflect(roof_norm, {0, 1, 0}), // front roof out
        glm::reflect(-roof_norm, {0, 1, 0}), // front roof in
        {0, 1, 0}, //up
        {0, -1, 0} //down
    };

    std::vector<int> normal_indices{
        // inside walls
        2,
        3,
        0,
        //forward wall
        1,
        1,
        1,
        1,
        1,
        1,
        1,
        1,
        1,

        // outside walls
        0,
        1,
        2,
        //forward wall
        3,
        3,
        3,
        3,
        3,
        3,
        3,
        3,
        3,

        //top of roof
        6,
        4,
        //under of roof
        7,
        5,
        0,
        0,
        1,
        2,
        2,
        3,

        //door frame
        2,
        9,
        0,
        //window 1 frame
        2,
        9,
        0,
        8,
        //window 2 frame
        2,
        9,
        0,
        8,
    };

    std::vector<material> materials{
        {
            {0.8667, 0.8672, 0.8437, 1},
            {0.8667, 0.8672, 0.8437, 1},
            {.1, .1, .1, 1},
            50,
            {0, 0, 0, 0}
        },
        {
            {0.8242, 0.8242, .7812,  1},
            {0.8242, 0.8242, .7812,  1},
            {.1, .1, .1, 1},
            50,
            {0, 0, 0, 0}
        },
        {
            {0.4196, 0.4941, .5176,  1},
            {0.4196, 0.4941, .5176,  1},
            {.1, .1, .1, 1},
            50,
            {0, 0, 0, 0}
        }
    };

    std::vector<int> material_indices{
        // inside walls
        1, // right
        0, // away
        1, // left
        //toward
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,

        // outside walls
        0,
        0,
        0,
        //forward wall
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,

        //top of roof
        2,
        2,
        //underside of roof
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,

        //door frame
        0,
        0,
        0,
        //window 1 frame
        0,
        0,
        0,
        0,
        //window 2 frame
        0,
        0,
        0,
        0,
    };

    //#dedfda

    for (size_t i = 0; i < polygons.size(); i++) {
        const auto &polygon = polygons[i];
//        glColor3fv(glm::value_ptr(color));
        materials[material_indices[i]].load();
        glNormal3fv(glm::value_ptr(normals[normal_indices[i]]));
        glBegin(GL_POLYGON);
        for (auto index : polygon) {
            glVertex3fv(glm::value_ptr(points[index]));
        }
        glEnd();
    }
}
