
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <glm/glm.hpp>
#include <vector>
#include <random>
#include <array>
#include <glm/gtc/type_ptr.hpp>
#include <iterator>
#include <memory>
#include "appStates.h"
#include "globalState.h"


std::unique_ptr<AppState> currentState = std::make_unique<InitialAppState>();
std::array<glm::vec3, 36> bigSquareColors = currentState->bigSquareColors();
std::array<glm::vec3, 16> littleSquareColors = currentState->littleSquareColors();
glm::mat4 camera = currentState->getCamera();

const float animHalfLifeMs = 500;
const uint animPeriodMs = 50;

template<typename T>
void slideTowards(T &from, const T &to, float fraction) {
    from = to + (from - to) * fraction;
}


void animate(int) {

    if (std::isnan(camera[0][0])) camera = currentState->getCamera();

    auto m = static_cast<float>(std::pow(.5, animPeriodMs / animHalfLifeMs));
    slideTowards(camera, currentState->getCamera(), m);

    auto targetBigSquareColors = currentState->bigSquareColors();
    for (int i = 0; i < bigSquareColors.size(); i++) {
        slideTowards(bigSquareColors[i], targetBigSquareColors[i], m);
    }

    auto targetLittleSquareColors = currentState->littleSquareColors();
    for (int i = 0; i < littleSquareColors.size(); i++) {
        slideTowards(littleSquareColors[i], targetLittleSquareColors[i], m);
    }

    glutPostRedisplay();
    glutTimerFunc(animPeriodMs, animate, 1);
}

void drawScene() {
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(&camera[0][0]);

    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            auto color = bigSquareColors[i * 6 + j];
            glColor3f(color.r, color.g, color.b);
            glBegin(GL_POLYGON);
            glVertex3d(0 - 5 * i, 0 + 5 * j, 2);
            glVertex3d(0 - 5 * i, 5 + 5 * j, 2);
            glVertex3d(-5 - 5 * i, 5 + 5 * j, 2);
            glVertex3d(-5 - 5 * i, 0 + 5 * j, 2);
            glEnd();
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            auto color = littleSquareColors[i * 4 + j];
            glColor3f(color.r, color.g, color.b);
            glBegin(GL_POLYGON);
            glVertex3d(0 + 5 * i, 0 - 5 * j, 0);
            glVertex3d(0 + 5 * i, -5 - 5 * j, 0);
            glVertex3d(5 + 5 * i, -5 - 5 * j, 0);
            glVertex3d(5 + 5 * i, 0 - 5 * j, 0);
            glEnd();
        }
    }


    glDisable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, 0, 1);

    glColor3f(1, 1, 1);
    glBegin(GL_POINTS);
    glVertex3f(-.5f, .5f, -.5f);
    glVertex3f(-.5f, -.5f, -.5f);
    glVertex3f(.5f, .5f, -.5f);
    glVertex3f(.5f, -.5f, -.5f);
    glVertex3f(0, 0, -.5f);
    glEnd();

    glutSwapBuffers();

    GLenum err;
    if ((err = glGetError()) != GL_NO_ERROR) {
        std::cout << err;
    }
}

// Initialization routine.
void setup() {
    glEnable(GL_MULTISAMPLE);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glutTimerFunc(animPeriodMs, animate, 1);
}

// OpenGL window reshape routine.
void resize(int w, int h) {
    width = w;
    height = h;
    glViewport(0, 0, w, h);
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
            exit(0);
        case ' ':
            currentState = currentState->nextState();
        default:
            break;
    }
}

// Main routine.
int main(int argc, char **argv) {
    glutInit(&argc, argv);

    glutInitContextVersion(3, 0);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);

    glutInitWindowSize(850, 600);
    glutInitWindowPosition(0, 0);

    glutCreateWindow("square.cpp");

    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);

    glewExperimental = GL_TRUE;
    glewInit();

    setup();

    glutMainLoop();
}