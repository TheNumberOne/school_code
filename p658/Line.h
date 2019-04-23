#pragma once

#include "./util.h"
#include "./programs.h"

class Line {
 public:
  static Line* instance() {
    if (!_instance) {
      _instance = new Line();
    }
    return _instance;
  }

 private:
  Line() {
    vertices[0] = Point(0, 0);
    vertices[1] = Point(1, 0);

    glGenBuffers(1, &vertex_buffer);
    // std::cout << vertex_buffer << std::endl;

    // glBindBuffer(GL_ARRAY_BUFFER, 2);
    // glBindBuffer(GL_ARRAY_BUFFER, 1);
    // glBindBuffer(GL_ARRAY_BUFFER, 2);
    // glBindBuffer(GL_ARRAY_BUFFER, 1);

    check_gl_error();
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, 2*sizeof(Point), vertices,
                 GL_STATIC_DRAW);
  }

 public:
  void render(
      FlatProgram& program, mat4x4 mvp_, const Point& a, const Point& b,
              const Color& c) const {
    mat4x4 mvp;
    mat4x4_dup(mvp, mvp_);


    Point verts[] = { a, b };
    // std::cout << a.x << " " << a.y << std::endl;

    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    // glBufferData(GL_ARRAY_BUFFER, 2*sizeof(Point), verts,
    //              GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, 2*sizeof(Point), verts);

    glEnableVertexAttribArray(program.vpos_location);
    glVertexAttribPointer(program.vpos_location, 2, GL_FLOAT, GL_FALSE,
                          sizeof(float) * 2, (void*) 0);
    // mat4x4 m;
    // mat4x4_identity(m);
    // mat4x4_translate(m, a.x, a.y, 0);
    // const float len = sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
    // mat4x4_scale_aniso(m, m, len, 1, 1);
    // const float theta = atan2(b.y-a.y, b.x-a.x);
    // std::cout << theta << std::endl;
    // mat4x4_rotate_Z(m, m, theta);
    // mat4x4_mul(mvp, mvp, m);
    glUniformMatrix4fv(program.mvp_location, 1, GL_FALSE, (const GLfloat*) mvp);

    // Color c = Color::BLACK;
    glUniform3fv(program.color_location, 1, (const GLfloat*)&c);
    glDrawArrays(GL_LINES, 0, 2);
  }

  

 private:
  static Line* _instance;
  Point vertices[2];
  GLuint vertex_buffer;
};
