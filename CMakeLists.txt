

cmake_minimum_required(VERSION 3.26)
project(AlgorithmCPP)

set(CMAKE_CXX_STANDARD 14)


include_directories(.)
include_directories(src)
include_directories(src/test)

add_executable(AlgorithmCPP
        src/basis/binary_search.cpp
        README.md)

add_executable(main_problem_0 "src/test/leetcode/problem_0.cpp")
add_executable(main_problem_1 "src/test/leetcode/problem_1.cpp")