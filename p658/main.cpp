//------------------------------------------------------------
//
// CS 3385
// Project p658
//
// GETTING SETUP
//
// In this project you will implement Dijkstra's algorithm and
// apply it to finding shortest paths between vertices
// according to cartesian distance traveled.
//
// This project uses OpenGL. There are a few differences as a
// result:
//
// Linux/Mac users: This project uses CMake. To see if it is
// installed on your system, type "cmake --version" at the
// command-line. In the unlikely event that it is not installed
// on your system, you can download from the cmake website and
// install or use a package manager such as apt-get (Debian)
// or ports (MacOS). Once cmake is installed, do the following
// to compile:
//   1) Navigate to the project directory on the command-line
//   2) > mkdir release
//   3) > cd release
//   4) > cmake ..
//   5) > make
//   6) > ./dijkstra
//
// Windows users: A VisualStudio project is provided for you.
// Open the dijkstra.sln solution file in VisualStudio and
// you should then be able to compile and run. When debugging,
// use the "dijkstra" target. VisualStudio 2017 users: you may
// need to go to the property pages for each of the two projects
// and change General > Windows SDK Version to 10.
//
// PROJECT REQUIREMENTS
//
// You will implement a graph data structure (you're welcome to
// copy your graph from project p595 into the appropriate 
// places in Graph.h). The graph will have a few minor 
// modifications as noted in Graph.h and will have
// a function called dijkstra(). Once you've implemented
// dijkstra(), you will update the visualization to show the
// shortest path from a target vertex back to a source vertex.
//
// To see what your completed project should look and behave
// like, watch the video at youtu.be/OMBsAxMbMKU.
//
// The first place to look to understand the code is initGraph(),
// implemented in Graph.cpp. You will need to implement your
// graph in such a way that vertices have both a data label
// and a current position. The weight of an edge between two
// vertices is the distance between two vertices. See the
// function distance() in util.h to help with that. After
// initGraph() is uncommented and working, take a look at
// Graph::render(). 
//
// Scoring: you will receive full credit if your project
// behaves as described in the video. You can earn extra credit
// in this project by enhancing the user experience: allowing
// the user to add/remove vertices and edges; changing colors
// in interesting ways; selecting and moving multiple vertices;
// drawing text (this is a challenge); allowing multiple targets
// and finding the shortest paths that don't overlap; etc.
// Let your imagination run wild. Really spectacular projects can
// earn up to 20 points extra credit.
//
// If you do implement extra credit, keep in mind that you should
// make changes only to the three files you will be submitting.
// You will not need to make changes to main.cpp to implement the
// base functionality -- main.cpp need only change for extra
// credit functionality. Please submit a file named extra.txt
// listing the changes you made.
//
// You do not need to run code checker on this project.
//
// Files to submit:
//   * Graph.h
//   * Graph.cpp
//   * main.cpp (submit even if you haven't changed it)
//   * extra.txt (submit only if you did extra credit)
// 
//------------------------------------------------------------
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "linmath.h"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "./util.h"
#include "./Circle.h"
#include "./Line.h"
#include "./Vertex.h"
#include "./programs.h"
#include "./Graph.h"

Color Color::WHITE = Color(1, 1, 1);
Color Color::BLACK = Color(0, 0, 0);
Color Color::GRAY = Color(0.7, 0.7, 0.7);
Color Color::RED = Color(1, 0, 0);
Color Color::GREEN = Color(0, 1, 0);
Color Color::BLUE = Color(0, 0, 1);
Color Color::BROWN = Color(0.6, 0.3, 0);

Circle* Circle::_instance = 0;
Line* Line::_instance = 0;

static const int WIDTH = 640;
static const int HEIGHT = 480;

GLFWwindow* window;
float wratio;

// Global graph variable
Graph g;

static void error_callback(int error, const char* description) {
  fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(
    GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

Point win2obj(double xwin, double ywin) {
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);

  return Point(wratio*2*(xwin/(double)WIDTH)-wratio, 0-(2*(ywin/(double)HEIGHT)-1));
}

bool moving = false;
void mouse_button_callback(
    GLFWwindow* window, int button, int action, int mods) {
  using namespace std;
  if (action == GLFW_PRESS) {
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    Point p = win2obj(x, y);
    if (mods & GLFW_MOD_CONTROL) {
      g.mouseControlClick(p);
    } else if (mods & GLFW_MOD_SHIFT) {
      g.mouseShiftClick(p);
    } else if (mods == 0) {
      moving = true;
      g.mouseDown(p);
    }
  } else if (action == GLFW_RELEASE) {
    moving = false;
  }
}

void cursor_pos_callback(GLFWwindow* window, double x, double y) {
  if (moving) {
    Point p = win2obj(x, y);
    g.mouseMoved(p);
  }
}

void render(FlatProgram& program) {
  mat4x4 m, p, mvp;

  glClearColor(1, 1, 1, 0);
  glClear(GL_COLOR_BUFFER_BIT);

  mat4x4_identity(m);
  mat4x4_ortho(p, -wratio, wratio, -1.f, 1.f, 1.f, -1.f);
  mat4x4_mul(mvp, p, m);

  glUseProgram(program.program);
  glUniformMatrix4fv(program.mvp_location, 1, GL_FALSE, (const GLfloat*) mvp);

  g.render(program, mvp);
}

int main(void) {
  using namespace std;

  glfwSetErrorCallback(error_callback);

  if (!glfwInit())
    exit(EXIT_FAILURE);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

  window = glfwCreateWindow(WIDTH, HEIGHT, "Dijkstra", NULL, NULL);
  if (!window) {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwSetKeyCallback(window, key_callback);
  glfwSetMouseButtonCallback(window, mouse_button_callback);
  glfwSetCursorPosCallback(window, cursor_pos_callback);

  glfwMakeContextCurrent(window);
  gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
  glfwSwapInterval(1);

  Circle::instance();
  Line::instance();

  FlatProgram program;
  initGraph(g);

  while (!glfwWindowShouldClose(window)) {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    wratio = width / (float) height;
    glViewport(0, 0, width, height);

    render(program);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);

  glfwTerminate();
  exit(EXIT_SUCCESS);
}

