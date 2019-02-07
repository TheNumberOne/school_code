cmake_minimum_required(VERSION 3.13)
project(project1)

set(CMAKE_CXX_STANDARD 17)

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})
link_libraries(${GLUT_LIBRARIES})

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_libraries(${OPENGL_LIBRARIES})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_libraries(${GLEW_LIBRARIES})

find_package(glm REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})
link_libraries(${GLM_LIBRARIES})

add_executable(project1
        main.cpp appStates.cpp appStates.h globalState.cpp globalState.h colors.cpp colors.h)
add_executable(example rotatingHelix2.cpp)