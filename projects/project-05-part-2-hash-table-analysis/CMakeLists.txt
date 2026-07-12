cmake_minimum_required(VERSION 3.20)
project(project_05_part_2)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src/implementations/BinaryHeapInVector)
add_subdirectory(src/implementations/BinomialQueues)
add_subdirectory(src/implementations/HashTablesOpenAddressing)


add_executable(top_level_main
        main.cpp
        src/harness/RunResults.hpp
)


add_executable(harness
        src/harness/Operation.hpp
        src/harness/main.cpp
        src/implementations/BinaryHeapInVector/BinaryHeapInVector.cpp
        src/implementations/BinaryHeapInVector/BinaryHeapInVector.hpp
        utils/comparator.cpp
        src/implementations/BinomialQueues/BinomialQueue.cpp
        src/implementations/BinomialQueues/BinomialQueue.hpp
        src/implementations/BinomialQueues/BQnode.cpp
        src/harness/RunMetaData.hpp
        src/implementations/LinearBaseLine/LinearBaseLine.cpp
        src/implementations/LinearBaseLine/LinearBaseLine.hpp
        src/implementations/Oracle/QuadraticOracle.cpp
        src/implementations/Oracle/QuadraticOracle.hpp
)

add_executable(huffman_trace
        src/trace-generators/huffman_coding/main.cpp
)

add_executable(batch_then_drain_trace
        src/trace-generators/batch_then_drain/main.cpp
)

add_executable(hash_harness
        src/hash_harness/main.cpp                         # <-- new main()
        src/implementations/HashTablesOpenAddressing/HashTableDictionary.cpp
        src/implementations/HashTablesOpenAddressing/HashTableDictionary.hpp
        src/implementations/HashTablesOpenAddressing/Operations.hpp
        src/implementations/HashTablesOpenAddressing/InvertedListDictionary.cpp
        src/implementations/HashTablesOpenAddressing/InvertedListDictionary.hpp
        src/implementations/HashTablesOpenAddressing/SmallIntMixedOperations.cpp
        src/implementations/HashTablesOpenAddressing/SmallIntMixedOperations.hpp
        src/hash_harness/Operation.hpp

        src/hash_harness/RunMetaData.hpp
)
add_executable(lru_profile_trace
        src/trace-generators/lru_profile/main.cpp
)
