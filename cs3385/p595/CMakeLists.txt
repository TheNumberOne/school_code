cmake_minimum_required(VERSION 3.13)
project(p595)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(p595
        bacon.cpp
        bacon.h
        Graph.h
        main.cpp
        util.h)
