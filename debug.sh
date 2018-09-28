#!/bin/bash
mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug .. && make && valgrind --leak-check=yes LinkedList/LinkedList
cd ..
