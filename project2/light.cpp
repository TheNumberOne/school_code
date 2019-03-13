
#include <GL/glew.h>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "light.hpp"


void drawLightSource()
{
    glm::vec4 ambience{0, 0, 0, 1};
    glm::vec4 lightColor{.9, .9, .9, 1};
    glm::vec4 lightPosition{0, 4, 0, 1};
    glLightfv(GL_LIGHT0, GL_AMBIENT, glm::value_ptr(ambience));
    glLightfv(GL_LIGHT0, GL_DIFFUSE, glm::value_ptr(lightColor));
    glLightfv(GL_LIGHT0, GL_SPECULAR, glm::value_ptr(lightColor));
    glLightfv(GL_LIGHT0, GL_POSITION, glm::value_ptr(lightPosition));
    
    
    glm::vec4 green{0, 1, 0, 1};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(green));
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(green));
    glPointSize(10);
    glBegin(GL_POINTS);
    glVertex3fv(glm::value_ptr(lightPosition));
    glEnd();
}