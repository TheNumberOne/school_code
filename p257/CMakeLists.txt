cmake_minimum_required(VERSION 3.13)
project(p257)

set(CMAKE_CXX_STANDARD 98)

include_directories(.)

add_executable(p257
        hash.h
        HashTable.h
        LinkedList.h
        main.cpp
        Person.h
        Student.h
        util.h)
