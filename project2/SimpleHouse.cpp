#include <glm/vec3.hpp>
#include <vector>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include "SimpleHouse.hpp"

static void loadWallMaterial()
{
    glm::vec4 color{1, 0, 0, 1};
    glm::vec4 diffuse{.5, 0, 0, 1};
    glm::vec4 specular{.1, .1, .1, 1};
    float shininess = 50;
    glm::vec4 emissions{0, 0, 0, 0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(color));
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(diffuse));
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(specular));
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &shininess);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, glm::value_ptr(emissions));
}

void SimpleHouse::draw()
{
    loadWallMaterial();
    
    float frontHeight = 5;
    float backHeight = 5;
    float width = 20;
    float length = 13;
    glm::vec3 color{1, .1, .1};
    
    std::vector<std::vector<glm::vec3>> shapes{
        {//front wall
            {width / 2,     0,           length / 2},
            {width / 2,     frontHeight, length / 2},
            {-width / 2,     frontHeight, length / 2},
            {-width / 2,     0,           length / 2},
        },
        {//left wall
            {-width / 2,    0,           length / 2},
            {-width / 2,    frontHeight, length / 2},
            {-width / 2,     backHeight,  -length / 2},
            {-width / 2,     0,           -length / 2},
        },
        {//right wall
            {width / 2,     0,           -length / 2},
            {width / 2,     backHeight,  -length / 2},
            {width / 2,      frontHeight, length / 2},
            {width / 2,      0,           length / 2},
        },
        {//back wall
            {-width / 2,    0,           -length / 2},
            {-width / 2,    backHeight,  -length / 2},
            {width / 2,      backHeight,  -length / 2},
            {width / 2,      0,           -length / 2},
        },
        {//ceiling
            {width / 2 + 1, frontHeight, length / 2 + 1},
            {width / 2 + 1, backHeight,  -length / 2 - 1},
            {-width / 2 - 1, backHeight,  -length / 2 - 1},
            {-width / 2 - 1, frontHeight, length / 2 + 1},
        }
    };
    std::vector<glm::vec3> normals{
        {0,  0, 1},
        {-1, 0, 0},
        {1,  0, 0},
        {0,  0, -1},
        {0,  1, 0}
    };
    
    for (size_t i = 0; i < shapes.size(); i++) {
        const auto &shape = shapes[i];
//        glColor3fv(glm::value_ptr(color));
        glNormal3fv(glm::value_ptr(normals[i]));
        glBegin(GL_POLYGON);
        for (const auto &point : shape) {
            glVertex3fv(glm::value_ptr(point));
        }
        glEnd();
    }
}
