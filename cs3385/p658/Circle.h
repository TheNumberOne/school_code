#pragma once

#include "./util.h"
#include "./programs.h"

class Circle {
 public:
  static Circle* instance() {
    if (!_instance) {
      _instance = new Circle();
    }
    return _instance;
  }

 private:
  Circle() {
    vertices[0] = Point(0, 0);
    const float inc = 360 / (float)(NUM_VERTICES-2);
    for (int i = 0; i < NUM_VERTICES-1; ++i) {
      const float theta = i * inc;
      const float x = cos(radians(theta));
      const float y = sin(radians(theta));
      vertices[i+1] = Point(x, y);
    }
    vertices[NUM_VERTICES-1] = vertices[1];

    glGenBuffers(1, &vertex_buffer);
    // std::cout << vertex_buffer << std::endl;
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, NUM_VERTICES*sizeof(Point), vertices,
                 GL_STATIC_DRAW);
  }

 public:
  void render(
      FlatProgram& program, mat4x4 mvp_, const Point& position, const Color& c,
      const bool filled) const {
    mat4x4 mvp;
    mat4x4_dup(mvp, mvp_);

    check_gl_error();
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    check_gl_error();
    // glBindBuffer(GL_ARRAY_BUFFER, 1);

    glEnableVertexAttribArray(program.vpos_location);
    glVertexAttribPointer(program.vpos_location, 2, GL_FLOAT, GL_FALSE,
                          sizeof(float) * 2, (void*) 0);
    mat4x4 m, s;
    mat4x4_identity(m);
    mat4x4_identity(s);
    mat4x4_translate(m, position.x, position.y, 0);
    mat4x4_scale_aniso(m, m, 0.05, 0.05, 1);
    mat4x4_mul(mvp, mvp, m);
    glUniformMatrix4fv(program.mvp_location, 1, GL_FALSE, (const GLfloat*) mvp);

    check_gl_error();
    glUniform3fv(program.color_location, 1, (const GLfloat*)&c);
    check_gl_error();
    if (filled) {
      glDrawArrays(GL_TRIANGLE_FAN, 0, NUM_VERTICES);
    } else {
      glDrawArrays(GL_LINE_STRIP, 1, NUM_VERTICES-1);
    }
    check_gl_error();
  }

  

 private:
  static const int NUM_VERTICES = 38;

  static Circle* _instance;
  Point vertices[NUM_VERTICES];
  GLuint vertex_buffer;
};
