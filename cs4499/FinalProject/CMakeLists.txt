cmake_minimum_required(VERSION 3.0...3.14)
project(FinalProject)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(FinalProject main.cpp)
target_link_libraries(FinalProject ${Boost_LIBRARIES})