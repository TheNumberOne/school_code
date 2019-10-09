cmake_minimum_required(VERSION 3.13)
project(p307)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(p307
        BinarySearchTree.h
        main.cpp
        Student.h
        util.h)
