#pragma once

#include "./Circle.h"

class DVertex {
 public:
  DVertex() {
    _position = Point(0.5, 0);
    _circle = Circle::instance();
    _color = Color::WHITE;
    _filled = false;
  }

  void render(FlatProgram& program, mat4x4 mvp) const {
    _circle->render(program, mvp, _position, _color, _filled);
  }

  Point position() {
    return _position;
  }

  void setPosition(const Point& p) {
    _position = p;
  }

  Color color() {
    return _color;
  }

  void setColor(const Color& c) {
    _color = c;
  }

  bool filled() {
    return _filled;
  }

  void setFilled(const bool& f) {
    _filled = f;
  }

 private:
  Point _position;
  Color _color;
  bool _filled;
  Circle* _circle;
};
