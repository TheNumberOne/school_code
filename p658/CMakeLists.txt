cmake_minimum_required(VERSION 2.8.12)
project(Dijkstra)

#------------------------------------------------------------
# Use C++ 11
#------------------------------------------------------------
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
if(COMPILER_SUPPORTS_CXX11)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
else()
  message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

add_subdirectory(glfw)
#add_subdirectory(${GLFW_SOURCE_DIR})
#set(GLFW_SOURCE_DIR glfw-3.2.1)

link_libraries(glfw)

include_directories(${glfw_INCLUDE_DIRS})

if (MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()


include_directories("${GLFW_SOURCE_DIR}/deps")

set(GLAD "${GLFW_SOURCE_DIR}/deps/glad/glad.h"
         "${GLFW_SOURCE_DIR}/deps/glad.c")

add_executable(dijkstra WIN32 main.cpp Graph.cpp ${GLAD})
set(WINDOWS_BINARIES dijkstra)

if (MSVC)
    # Tell MSVC to use main instead of WinMain for Windows subsystem executables
    set_target_properties(${WINDOWS_BINARIES} PROPERTIES
                          LINK_FLAGS "/ENTRY:mainCRTStartup")
endif()
