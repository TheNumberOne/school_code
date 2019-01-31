cmake_minimum_required(VERSION 3.13)
project(p157)

set(CMAKE_CXX_STANDARD 98)

include_directories(.)

add_executable(p157
        Heap.cpp
        Heap.h
        main.cpp)
