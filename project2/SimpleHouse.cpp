#include <glm/vec3.hpp>
#include <vector>
#include <GL/glew.h>
#include "SimpleHouse.hpp"


void SimpleHouse::draw()
{
    float frontHeight = 10;
    float backHeight = 20;
    float width = 50;
    float length = 20;
    glm::vec3 color{1, .1, .1};
    
    std::vector<std::vector<glm::vec3>> shapes{
        {//front wall
            {-width / 2, 0, length / 2},
            {-width / 2, frontHeight, length / 2},
            {width / 2,  frontHeight, length / 2},
            {width / 2,  0, length / 2}
        },
        {//left wall
            {-width / 2, 0, -length / 2},
            {-width / 2, backHeight,  -length / 2},
            {-width / 2, frontHeight, length / 2},
            {-width / 2, 0, length / 2}
        },
        {//right wall
            {width / 2,  0, length / 2},
            {width / 2,  frontHeight, length / 2},
            {width / 2,  backHeight,  -length / 2},
            {width / 2,  0, -length / 2}
        },
        {//back wall
            {width / 2,  0, -length / 2},
            {width / 2,  backHeight,  -length / 2},
            {-width / 2, backHeight,  -length / 2},
            {-width / 2, 0, -length / 2}
        }
    };
    
    for (const auto &shape : shapes
        ) {
        glColor3f((float) rand() / RAND_MAX, (float) rand() / RAND_MAX, (float) rand() / RAND_MAX);
        glBegin(GL_POLYGON);
        for (const auto &point : shape
            ) {
            glVertex3fv(&point[0]);
        }
        glEnd();
    }
}
