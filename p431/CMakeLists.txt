cmake_minimum_required(VERSION 3.13)
project(p431)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(p431
        bit_buffer.h
        huffman.cpp
        huffman.h
        main.cpp
        util.h)
