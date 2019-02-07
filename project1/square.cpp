
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

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/rotate_vector.hpp>
#include "appStates.h"


int width, height;

std::vector<glm::vec3> cameraPositions{
        {0,  0,  30},
        {20, 20, 30},
        {4,  0,  50}
};

std::vector<glm::vec3> lookPositions{
        {0,    0,   1},
        {0,    0,   1},
        {-2.5, 2.5, 1}
};
int cameraIndex = 0;

glm::vec3 cameraPosition = cameraPositions[cameraIndex];
glm::vec3 targetCameraPosition = cameraPosition;
glm::vec3 lookPosition = lookPositions[cameraIndex];
glm::vec3 targetLookPosition = lookPosition;
float msHalfLife = 500;
uint animPeriod = 50;

auto getRng() {
    std::random_device rd;
    std::default_random_engine re(rd());
    return re;
}

glm::vec3 generateRandomColor() {
    static auto rng = getRng();
    static auto dist = std::uniform_real_distribution<float>();
    return {dist(rng), dist(rng), dist(rng)};
}

template<size_t width, size_t height>
std::array<std::array<glm::vec3, width>, height> generateColors() {
    std::array<std::array<glm::vec3, width>, height> ret{};
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            ret[i][j] = generateRandomColor();
        }
    }
    return ret;
}


template<size_t width, size_t height>
std::array<std::array<glm::vec3, width>, height> oneColor(glm::vec3 c) {
    std::array<std::array<glm::vec3, width>, height> ret{};
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            ret[i][j] = c;
        }
    }
    return ret;
}

std::array<std::array<glm::vec3, 6>, 6> firstSquareColors = oneColor<6, 6>({1, 0, 0});
std::array<std::array<glm::vec3, 4>, 4> secondSquareColors = oneColor<4, 4>({0, 0, 1});
std::array<std::array<glm::vec3, 6>, 6> firstSquareTargetColors = oneColor<6, 6>({1, 0, 0});
std::array<std::array<glm::vec3, 4>, 4> secondSquareTargetColors = oneColor<4, 4>({0, 0, 1});



void animate(int _) {
    auto m = static_cast<float>(std::pow(.5, animPeriod / msHalfLife));
    cameraPosition = targetCameraPosition + (cameraPosition - targetCameraPosition) * m;
    lookPosition = targetLookPosition + (lookPosition - targetLookPosition) * m;

    for (int i = 0; i < firstSquareColors.size(); i++) {
        for (int j = 0; j < firstSquareColors[i].size(); j++) {
            firstSquareColors[i][j] =
                    firstSquareTargetColors[i][j] + (firstSquareColors[i][j] - firstSquareTargetColors[i][j]) * m;
        }
    }

    for (int i = 0; i < secondSquareColors.size(); i++) {
        for (int j = 0; j < secondSquareColors[i].size(); j++) {
            secondSquareColors[i][j] =
                    secondSquareTargetColors[i][j] + (secondSquareColors[i][j] - secondSquareTargetColors[i][j]) * m;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(animPeriod, animate, 1);
}

glm::vec2 toWindowCoords(glm::vec3 v) {
    float m[16];
    glGetFloatv(GL_PROJECTION_MATRIX, m);
    glm::mat4 project = glm::make_mat4(m);
    glGetFloatv(GL_MODELVIEW_MATRIX, m);
    glm::mat4 modelView = glm::make_mat4(m);
    glm::vec4 firstCenter = project * modelView * glm::vec4(v, 1);
    return firstCenter / firstCenter.w;
}

/**
 * Calculates the matrix that centers the centers of the two squares in the upper left and lower right corners.
 * @return
 */
glm::mat4 calculateThirdPerspectiveMatrix() {
    glm::vec3 redCenter{-15, 15, 2};
    glm::vec3 blueCenter{10, -10, 0};
    glm::vec3 center = (redCenter + blueCenter) / 2.f;
    float distance = 50;
    glm::vec3 cameraPosition = glm::normalize(glm::cross(blueCenter - center, {0, 1, 0})) * distance;

    auto theta = static_cast<float>(std::atan2(height, width));
    float width = glm::length(redCenter - center);

    float near = distance / 2;
    float far = distance * 2;
    float right = width * std::cos(theta);
    float left = -right;
    float top = width * std::sin(theta);
    float bottom = -top;

    // First look at the center of the two centers with the red center oriented upwards.
    glm::mat4 camera = glm::lookAt(cameraPosition, center, redCenter - center);

    // Then rotate the image such that the centers align along the diagonal from upper left
    // to lower right.
    camera = glm::rotate(3.1415926f / 2 - theta, glm::vec3{0, 0, 1}) * camera;

    // Then convert that to a perspective view.
//    camera = glm::frustum(left, right, bottom, top, near, far) * camera;

    camera = glm::ortho(left * 2, right * 2, bottom * 2, top * 2, near, far) * camera;

    return camera;
}

void drawScene() {
    glPushMatrix();


    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    if (cameraIndex == 2) {
        auto camera = calculateThirdPerspectiveMatrix();
        glLoadMatrixf(&camera[0][0]);
    } else {
        gluLookAt(cameraPosition.x, cameraPosition.y, cameraPosition.z, lookPosition.x, lookPosition.y, lookPosition.z,
                  0, 1, 0);
    }

    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            auto color = firstSquareColors[i][j];
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
            auto color = secondSquareColors[i][j];
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
    glMatrixMode(GL_MODELVIEW);

    glColor3f(1, 1, 1);
    glBegin(GL_POINTS);
    glVertex3f(-.5f, .5f, -.5f);
    glVertex3f(-.5f, -.5f, -.5f);
    glVertex3f(.5f, .5f, -.5f);
    glVertex3f(.5f, -.5f, -.5f);
    glVertex3f(0, 0, -.5f);
    glEnd();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glutSwapBuffers();
    glPopMatrix();
    GLenum err;
    if ((err = glGetError()) != GL_NO_ERROR) {
        std::cout << err;
    }
}

// Initialization routine.
void setup() {
    glEnable(GLUT_MULTISAMPLE);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glutTimerFunc(animPeriod, animate, 1);
}

// OpenGL window reshape routine.
void resize(int w, int h) {
    width = w;
    height = h;
    glViewport(0, 0, w, h);
    std::cout << w << " " << h << std::endl;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-30. * w / h, 30. * w / h, -30, 30, 20, 100);
//	glTranslatef(0, 0, -1);
//	glRotatef(10, 0, 1, 1);
//	glTranslatef(0, 0,-7.5);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
            exit(0);
        case ' ':
            cameraIndex++;
            cameraIndex %= cameraPositions.size();
            targetCameraPosition = cameraPositions[cameraIndex];
            targetLookPosition = lookPositions[cameraIndex];
            firstSquareTargetColors = generateColors<6, 6>();
            secondSquareTargetColors = generateColors<4, 4>();
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