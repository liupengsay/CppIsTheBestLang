

cmake_minimum_required(VERSION 3.26)
project(AlgorithmCPP)

set(CMAKE_CXX_STANDARD 14)


include_directories(.)
include_directories(src)
include_directories(test)


add_executable(main_problem_0 test/leetcode/problem_0.cpp)
add_executable(main_problem_1 test/leetcode/problem_1.cpp)
add_executable(binary_search src/basis/binary_search.cpp)
add_executable(template test/codeforces/template.cpp)
add_executable(diff_array src/basis/diff_array.cpp)
add_executable(fast_io src/fast_io.cpp)
add_executable(test_template test/template.cpp)
add_executable(struct_data_sort src/data_structure/struct_data_sort.cpp)
