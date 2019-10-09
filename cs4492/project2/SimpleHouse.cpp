#include <glm/vec3.hpp>
#include <vector>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.inl>
#include "SimpleHouse.hpp"
#include "rectangular_wall_with_holes.h"
#include "transformed_object.h"
#include "draw_container.h"
#include "slanted_roof.h"

void SimpleHouse::draw() const {
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
    float window_base_offset_y = 1;
    float width = 20; // Inside width
    float length = 13; // Inside length
    float door_center_x = .25f * width;
    float door_center_y = door_height / 2 + .01f;
    float window_1_center_x = -.25f * width;
    float window_2_center_x = 0;
    float windows_center_y = window_base_offset_y + window_height / 2;

    float walls_inside_x = width / 2;
    float walls_outside_x = walls_inside_x + wall_thickness;
    float walls_inside_z = length / 2;
    float walls_outside_z = walls_inside_z + wall_thickness;
    float walls_inside_y = wall_thickness * roof_pitch + height;
    float walls_outside_y = height;
    float walls_center_x = walls_inside_x + wall_thickness / 2;

    float roof_underside_height = walls_inside_z * roof_pitch; // height not including overhang
    float roof_underside_top_y = roof_underside_height + height;

    auto scene = draw_all(
        // roof
        transform(
            slanted_roof(walls_outside_x * 2, walls_outside_z * 2, roof_pitch, roof_thickness, overhang_length,
                         materials[0], materials[2]),
            glm::translate(glm::mat4(1), {0, height, 0})
        ),
        // front wall
        transform(
            wall{
                walls_inside_y,
                walls_outside_y,
                width,
                wall_thickness,
                {
                    {door_width, door_height, door_center_x, door_center_y},
                    {window_width, window_height, window_1_center_x, windows_center_y},
                    {window_width, window_height, window_2_center_x, windows_center_y},
                },
                materials[0]
            },
            glm::translate(glm::mat4(1), {0, 0, length / 2}) *
            glm::rotate(glm::mat4(1), glm::pi<float>(), {0, 1, 0})
        ),
        // back wall
        transform(
            wall{
                walls_inside_y,
                walls_outside_y,
                width,
                wall_thickness,
                {
                    {window_width, window_width, -width * 2 / 5, windows_center_y}
                },
                materials[0]
            },
            glm::translate(glm::mat4(1), {0, 0, -length / 2})
        ),
        // side walls
        multi_transform(
            multi_transform(
                wall{
                    roof_underside_top_y,
                    walls_outside_y,
                    wall_thickness,
                    length / 2 + wall_thickness,
                    {},
                    materials[1]
                },
                glm::mat4(1),
                glm::rotate(glm::mat4(1), glm::pi<float>(), {0, 1, 0})
            ),
            glm::translate(glm::mat4(1), {-walls_center_x, 0, 0}),
            glm::translate(glm::mat4(1), {walls_center_x, 0, 0})
        )
    );
    scene.draw();
}
