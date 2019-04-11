cmake_minimum_required(VERSION 3.13)
project(p565)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(p565
        bmp.cpp
        bmp.h
        Color.h
        DisjointSet.cpp
        DisjointSet.h
        main.cpp
        util.h)
