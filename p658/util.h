#pragma once

// for M_PI on Windows
#define _USE_MATH_DEFINES
#include <math.h>
#include <string>

struct Point {
  Point() : x(0), y(0) {}
  Point(float x_, float y_) : x(x_), y(y_) {}
  float x, y;
};

// Returns the distance between two points.
inline float distance(const Point& a, const Point& b) {
  return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

struct Color {
  Color() : r(0), g(0), b(0) {}
  Color(float r_, float g_, float b_) : r(r_), g(g_), b(b_) {}
  float r, g, b;

  static Color WHITE;
  static Color BLACK;
  static Color GRAY;
  static Color RED;
  static Color GREEN;
  static Color BLUE;
  static Color BROWN;
};

inline float degrees(const float rads) {
  return rads * 180 / M_PI;
}

inline float radians(const float degs) {
  return degs * M_PI / 180.0;
}

inline void clear_gl_errors() {
  while (glGetError() != GL_NO_ERROR);
}

// void print_error(const std::string& prefix, const bool stop) {
//   GLenum error = glGetError();
//   print_error(error, prefix, stop);
// }

inline std::string get_gl_error_msg(GLenum error) {
	std::string msg;

  switch (error) {
		case GL_NO_ERROR:
			msg = "GL_NO_ERROR - No error has been recorded. The value of this symbolic constant is guaranteed to be 0.";
			break;
		case GL_INVALID_ENUM:
			msg = "GL_INVALID_ENUM - An unacceptable value is specified for an enumerated argument. The offending command is ignored and has no other side effect than to set the error flag.";
			break;
		case GL_INVALID_VALUE:
			msg = "GL_INVALID_VALUE - A numeric argument is out of range. The offending command is ignored and has no other side effect than to set the error flag.";
			break;
		case GL_INVALID_OPERATION:
			msg = "GL_INVALID_OPERATION - The specified operation is not allowed in the current state. The offending command is ignored and has no other side effect than to set the error flag.";
			break;
		case GL_STACK_OVERFLOW:
			msg = "GL_STACK_OVERFLOW - This command would cause a stack overflow. The offending command is ignored and has no other side effect than to set the error flag.";
			break;
		case GL_STACK_UNDERFLOW:
			msg = "GL_STACK_UNDERFLOW - This command would cause a stack underflow. The offending command is ignored and has no other side effect than to set the error flag.";
			break;
		case GL_OUT_OF_MEMORY:
			msg = "GL_OUT_OF_MEMORY - There is not enough memory left to execute the command. The state of the GL is undefined, except for the state of the error flags, after this error is recorded.";
			break;
		// case GL_TABLE_TOO_LARGE:
		// 	msg = "GL_TABLE_TOO_LARGE - The specified table exceeds the implementation's maximum supported table size. The offending command is ignored and has no other side effect than to set the error flag.";
		// 	break;
		default:
			msg = "Unrecognized error";
			break;
  }
  return msg;
}

inline void print_gl_error(
		const GLenum error, const std::string& prefix, const bool stop) {
  if (error == GL_NO_ERROR) {
    return;
  }

  using namespace std;
  string msg = get_gl_error_msg(error);

  msg = prefix + ": glError: " + msg;
  cout << msg << endl;

  if (stop) {
    // throw logic_error(msg);
    exit(1);
  }
}

inline void print_gl_error(const GLenum error, const char* file, int line_number) {
  if (error == GL_NO_ERROR) {
    return;
  }

  using namespace std;
  string msg = get_gl_error_msg(error);
  cout << file << " line " << line_number << ": glError: " << msg << endl;
}

#define check_gl_error() { \
  GLenum error = glGetError(); \
  print_gl_error(error, __FILE__, __LINE__);  \
  clear_gl_errors(); \
}

#define ignore_gl_error() { glGetError(); }
