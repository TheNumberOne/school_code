cmake_minimum_required(VERSION 3.13)
project(p246)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(p246
        BinaryTree.h
        LinkedList.h
        main.cpp
        Person.h
        util.h)
