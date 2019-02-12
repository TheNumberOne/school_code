cmake_minimum_required(VERSION 3.13)
project(p171)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(p171
        bubble.h
        insertion.h
        main.cpp
        Person.h
        quicksort.h
        Song.h
        util.h)
