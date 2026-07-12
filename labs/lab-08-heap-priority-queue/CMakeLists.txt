cmake_minimum_required(VERSION 4.0)
project(HeapOrderedVectorBasedPQ)

set(CMAKE_CXX_STANDARD 20)

add_executable(HeapOrderedVectorBasedPQ main.cpp
        PriorityQueue.cpp
        PriorityQueue.hpp)
