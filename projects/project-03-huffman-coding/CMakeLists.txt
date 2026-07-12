cmake_minimum_required(VERSION 3.27.7)
project(p3_part1)

set(CMAKE_CXX_STANDARD 20)

add_executable(p3_part1 main.cpp
        Scanner.cpp
        Scanner.hpp
        utils.cpp
        utils.hpp
        BinSearchTree.cpp
        BinSearchTree.hpp
        PriorityQueue.cpp
        PriorityQueue.hpp
        TreeNode.hpp
        HuffmanTree.cpp
        HuffmanTree.hpp

)
