cmake_minimum_required(VERSION 3.13)
project(project1)

find_package(GLEW REQUIRED)
include_directories(GLEW_INCLUDE_DIRS)
link_libraries(${GLEW_LIBRARIES})


find_package(GLUT REQUIRED)
include_directories(GLUT_INCLUDE_DIRS)
link_libraries(${GLUT_LIBRARIES})

find_package(OpenGL REQUIRED)
include_directories(OPENGL_INCLUDE_DIR)
link_libraries(${OPENGL_LIBRARIES})

set(CMAKE_CXX_STANDARD 14)

add_executable(project1
        square.cpp)
