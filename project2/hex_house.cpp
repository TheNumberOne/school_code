#define GLM_ENABLE_EXPERIMENTAL

#include "hex_house.h"
#include "draw_container.h"
#include "rectangular_wall_with_holes.h"
#include "slanted_roof.h"
#include "walkway.h"
#include "door.h"
#include <glm/gtx/transform.hpp>

void hex_house::draw() const {
    float total_width = 20.7f;
    float total_length = 16.7f;
    std::vector<float> width_parts{
        12.2f,
        8.5f
    };
    std::vector<float> length_parts{
        8.5f,
        8.2f
    };
    float outside_wall_height = 3;
    float roof_slope = .25;
    float wall_thickness = .15;
    float roof_thickness = .25;
    float roof_overhang = 1;
    float inside_wall_height = outside_wall_height + wall_thickness * roof_slope;
    float door_width = .9;
    float door_height = 1.95;
    float door_stopper_size = .01;

    float inside_roof_height = roof_slope * length_parts[0] / 2 + inside_wall_height;

    glm::vec3 color1 = {0.8667, 0.8672, 0.8437};
    glm::vec3 color2 = {0.8667, 1, 0.8437};

    material material1{
        {.5f * color1, 1},
        {.5f * color1, 1},
        {.33, .33, .33, 1},
        2,
        {0, 0, 0, 0},
    };
    material material2{
        {.5f * color2, 1},
        {.5f * color2, 1},
        {.33, .33, .33, 1},
        2,
        {0, 0, 0, 0}
    };

    auto l_house = transform(
        draw_all(
            transform(
                // front wall
                wall{
                    inside_wall_height, outside_wall_height, total_width + wall_thickness * 2, wall_thickness, {
                        // front door
                        {door_width, door_height, .25f * total_width, door_height / 2 + door_stopper_size},
                        {3, 2.3, .4f * total_width, 1.16}
                    }, material1
                },
                glm::rotate(glm::pi<float>(), glm::vec3{0, 1, 0})
            ),
            //right wall
            transform(
                wall{
                    inside_wall_height, outside_wall_height, total_length, wall_thickness, {}, material1
                },
                glm::translate(glm::vec3{total_width / 2, 0, -total_length / 2}) *
                glm::rotate(-glm::pi<float>() / 2, glm::vec3{0, 1, 0})
            ),
            // closer back wall
            transform(
                wall{
                    inside_wall_height, outside_wall_height, width_parts[0] + wall_thickness, wall_thickness, {},
                    material2
                },
                glm::translate(glm::vec3{(width_parts[0] - total_width - wall_thickness) / 2, 0, -length_parts[0]})
            ),
            //rightmost left wall
            transform(
                wall{
                    inside_wall_height, outside_wall_height, length_parts[1], wall_thickness, {
                        {door_width, door_height, .25f * length_parts[1], door_height / 2 + door_stopper_size}
                    }, material2
                },
                glm::translate(glm::vec3{total_width / 2 - width_parts[1], 0, -length_parts[0] - length_parts[1] / 2}) *
                glm::rotate(glm::pi<float>() / 2, glm::vec3{0, 1, 0})
            ),
            // leftmost left wall
            transform(
                multi_transform(
                    wall{
                        inside_roof_height, inside_wall_height, wall_thickness, length_parts[0] / 2, {}, material1
                    },
                    glm::mat4(1),
                    glm::rotate(glm::pi<float>(), glm::vec3{0, 1, 0})
                ),
                glm::translate(glm::vec3{-wall_thickness / 2 - total_width / 2, 0, -length_parts[0] / 2})
            ),
            // farthest back wall
            transform(
                multi_transform(
                    wall{
                        inside_roof_height, outside_wall_height, wall_thickness, width_parts[1] / 2 + wall_thickness,
                        {},
                        material1
                    },
                    glm::mat4(1),
                    glm::rotate(glm::pi<float>(), glm::vec3{0, 1, 0})
                ),
                glm::translate(glm::vec3{total_width / 2 - width_parts[1] / 2, 0, -total_length}) *
                glm::rotate(-glm::pi<float>() / 2, glm::vec3{0, 1, 0}) *
                glm::translate(glm::vec3{-wall_thickness / 2, 0, 0})
            ),
            // front roof
            transform(
                slanted_roof{
                    total_width + 2 * wall_thickness, length_parts[0] + 2 * wall_thickness, roof_slope, roof_thickness,
                    roof_overhang, material1, true, glm::pi<float>() * 3 / 4
                },
                glm::translate(glm::vec3{0, outside_wall_height, -length_parts[0] / 2})
            ),
            // right roof
            transform(
                slanted_roof{
                    length_parts[1] + wall_thickness,
                    width_parts[1],
                    roof_slope, roof_thickness, roof_overhang + wall_thickness * std::sqrt(roof_slope * roof_slope + 1),
                    material1, true, glm::pi<float>() / 4
                },
                glm::translate(glm::vec3{total_width / 2 - width_parts[1] / 2, inside_wall_height,
                                         -length_parts[0] - length_parts[1] / 2 - wall_thickness / 2}) *
                glm::rotate(-glm::pi<float>() / 2, glm::vec3{0, 1, 0})
            ),
            // brick walkway
            transform(
                walkway(door_width + .2f, 5),
                glm::translate(glm::vec3{-.25f * total_width, 0, wall_thickness}) *
                glm::rotate(glm::pi<float>(), glm::vec3{0, 1, 0})
            ),
            // front door
            transform(
                door(door_width - .005f, door_height - .01f, wall_thickness / 2),
                glm::translate(glm::vec3{-.25f * total_width - .0025f, door_stopper_size, 0}) *
                glm::rotate(glm::pi<float>(), glm::vec3{0, 1, 0})
            ),
            transform(
                door(door_width - .005f, door_height - .01f, wall_thickness / 2),
                glm::translate(glm::vec3{total_width / 2 - width_parts[1], door_stopper_size,
                                         -length_parts[0] - length_parts[1] * .75 - .0025f}) *
                glm::rotate(glm::pi<float>() / 2, glm::vec3{0, 1, 0})
            )
        ),
        glm::translate(glm::vec3{-width_parts[1] / 2, 0, length_parts[0] / 2})
    );
    l_house.draw();
}
