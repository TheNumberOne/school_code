#!/bin/bash
cmake -DCMAKE_BUILD_TYPE=Debug .
make
valgrind --leak-check=yes LinkedList/LinkedList
