cmake_minimum_required(VERSION 3.13)
project(homework6)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(homework6
        Truck.cpp
        Truck.h
        Vehicle.cpp
        Vehicle.h main.cpp)
