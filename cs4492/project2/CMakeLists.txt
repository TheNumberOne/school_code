cmake_minimum_required(VERSION 3.13)
project(project2)

set(CMAKE_CXX_STANDARD 17)

find_package(GLUT REQUIRED STATIC)
include_directories(${GLUT_INCLUDE_DIR})

find_package(OpenGL REQUIRED COMPONENTS OpenGL)
include_directories(${OPENGL_INCLUDE_DIRS})

find_package(GLEW REQUIRED STATIC)
include_directories(${GLEW_INCLUDE_DIRS})

find_package(glm REQUIRED STATIC)
include_directories(${GLM_INCLUDE_DIRS})

find_package(SDL2 REQUIRED STATIC)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(TIFF REQUIRED STATIC)
include_directories(${TIFF_INCLUDE_DIRS})

add_executable(project2 main.cpp SimpleHouse.cpp SimpleHouse.hpp Camera.cpp Camera.hpp sdl.cpp sdl.hpp light.cpp light.hpp material.cpp material.hpp rectangular_wall_with_holes.cpp rectangular_wall_with_holes.h gl_util.cpp gl_util.h transformed_object.h draw_container.h slanted_roof.cpp slanted_roof.h display_lists_cache.h hex_house.cpp hex_house.h garage.cpp garage.h read_tiff_texture.cpp read_tiff_texture.h walkway.cpp walkway.h door.cpp door.h sphere.cpp sphere.h obj_model.cpp obj_model.h glm_util.cpp glm_util.h materials.cpp materials.h stb_image.h gl_util_texture.cpp gl_util_texture.h display_mesh.h display_mesh.cpp)
add_dependencies(project2 OpenGL::OpenGL)
target_link_libraries(project2 OpenGL::OpenGL ${GLEW_LIBRARIES} ${GLM_LIBRARIES} ${GLUT_LIBRARIES} ${SDL2_LIBRARIES} ${TIFF_LIBRARIES})

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})