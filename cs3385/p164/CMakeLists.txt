cmake_minimum_required(VERSION 3.13)
project(p164)

set(CMAKE_CXX_STANDARD 98)

include_directories(.)

add_executable(p164
        main.cpp
        Patient.h Heap.cpp Heap.h)
