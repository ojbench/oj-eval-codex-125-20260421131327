cmake_minimum_required(VERSION 3.10)
project(oj_problem_125)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(code code.cpp)

if (CMAKE_CXX_COMPILER_ID STREQUAL GNU)
    target_compile_options(code PRIVATE -O2 -pipe -s)
endif()
