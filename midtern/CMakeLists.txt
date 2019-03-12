cmake_minimum_required(VERSION 3.13)
project(midtern)

set(CMAKE_CXX_STANDARD 17)

add_executable(midtern main.cpp bunny.cpp bunny.hpp bunny_generator.cpp bunny_generator.hpp bunny_simulation.cpp bunny_simulation.hpp bunny_simulation_report.cpp bunny_simulation_report.hpp bunny_statistics.cpp bunny_statistics.hpp)