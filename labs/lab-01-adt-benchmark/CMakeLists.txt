cmake_minimum_required(VERSION 3.16)
project(DictionaryBenchmark)

set(CMAKE_CXX_STANDARD 20)

add_executable(DictionaryBenchmark
    main.cpp
    Dictionary.hpp
    UnsortedVectorDict.cpp
    UnsortedVectorDict.hpp
    SortedVectorDict.cpp
    SortedVectorDict.hpp
    UnsortedLinkedListDict.cpp
    UnsortedLinkedListDict.hpp
    SortedLinkedListDict.cpp
    SortedLinkedListDict.hpp
)


add_test(NAME AllTests COMMAND tests)
