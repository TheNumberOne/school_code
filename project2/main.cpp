
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <glm/glm.hpp>
#include <vector>
#include <random>
#include <array>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iterator>
#include <memory>
#include "SimpleHouse.hpp"

std::vector<std::vector<glm::vec3>> sides{
    {
        {1,  1,  -1},
        {1,  -1, -1},
        {-1, -1, -1},
        {-1, 1,  -1}
    },
    {
        {-1, 1,  -1},
        {-1, 1,  1},
        {1,  1,  1},
        {1,  1,  -1}
    },
    {
        {1,  -1, -1},
        {1,  1,  -1},
        {1,  1,  1},
        {1,  -1, 1}
    },
    {
        {-1, -1, -1},
        {1,  -1, -1},
        {1,  -1, 1},
        {-1, -1, 1}
    },
    {
        {-1, -1, 1},
        {-1, 1,  1},
        {-1, 1,  -1},
        {-1, -1, -1}
    },
    {
        {-1, -1, 1},
        {1,  -1, 1},
        {1,  1,  1},
        {-1, 1,  1}
    }
};

std::vector<glm::vec3> colors{
    {1,  0, 0},
    {0,  1, 0},
    {.5, 0, 1},
    {0,  0, 1},
    {1,  1, 0},
    {1,  1, 1}
};

void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 0, -50);
    
    SimpleHouse().draw();
    
    glDisable(GL_DEPTH_TEST);
    glutSwapBuffers();
    
    GLenum err;
    if ((err = glGetError()) != GL_NO_ERROR) {
        std::cout << err << std::endl;
    }
}

// Initialization routine.
void setup()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
//    glutTimerFunc(animPeriodMs, animate, 1);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    auto p = glm::perspective(glm::radians(90.f), (float) w / h, 5.0f, 1000.0f);
//    p = glm::rotate(p, glm::pi<float>(), {0, 1, 0});
    glLoadMatrixf(&p[0][0]);
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
    switch (key) {
        case 27: exit(0);
        default:break;
    }
}

// Main routine.
int main(int argc, char **argv)
{
    
    glutInit(&argc, argv);
    
    glutInitContextVersion(3, 0);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
    
    glutInitWindowSize(850, 600);
    glutInitWindowPosition(0, 0);
    
    glutCreateWindow("project2");
    
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    
    glewExperimental = GL_TRUE;
    glewInit();
    
    setup();
    
    glutMainLoop();
}