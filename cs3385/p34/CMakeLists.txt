cmake_minimum_required(VERSION 3.13)
project(p34)

set(CMAKE_CXX_STANDARD 98)

include_directories(.)

add_executable(p34
        main.cpp
        MergeSort.cpp
        MergeSort.h)
