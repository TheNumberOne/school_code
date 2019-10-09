cmake_minimum_required(VERSION 3.13)
project(p72)

set(CMAKE_CXX_STANDARD 98)

include_directories(.)

add_executable(p72
        main.cpp
        MaxSubarray.cpp
        MaxSubarray.h)
