cmake_minimum_required(VERSION 3.27.7)
project(reclistsStudentVersion)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(reclistsStudentVersion main.cpp lex.cpp parser.cpp reclists.cpp solutions.cpp
        solutions.cpp)
