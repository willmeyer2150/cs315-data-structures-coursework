cmake_minimum_required(VERSION 3.24)
project(recursiveListProblems)

set(CMAKE_CXX_STANDARD 20)

add_executable(recursiveListProblems main.cpp lex.cpp lex.hpp parser.cpp reclists.cpp reclists.hpp solutions.cpp solutions.hpp)
