cmake_minimum_required(VERSION 3.14)
project(stega)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(stega
        bmp.h
        stega.cpp)
