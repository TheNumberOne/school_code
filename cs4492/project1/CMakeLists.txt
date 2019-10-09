cmake_minimum_required(VERSION 3.13)
project(project1)

set(CMAKE_CXX_STANDARD 17)

find_package(GLUT REQUIRED STATIC)
include_directories(${GLUT_INCLUDE_DIR})

find_package(OpenGL REQUIRED COMPONENTS OpenGL)
include_directories(${OPENGL_INCLUDE_DIRS})

find_package(GLEW REQUIRED STATIC)
include_directories(${GLEW_INCLUDE_DIRS})

find_package(glm REQUIRED STATIC)
include_directories(${GLM_INCLUDE_DIRS})

add_executable(project1
        main.cpp appStates.cpp appStates.h globalState.cpp globalState.h colors.cpp colors.h)
add_dependencies(project1 OpenGL::OpenGL)
target_link_libraries(project1 OpenGL::OpenGL ${GLEW_LIBRARIES} ${GLM_LIBRARIES} ${GLUT_LIBRARIES})