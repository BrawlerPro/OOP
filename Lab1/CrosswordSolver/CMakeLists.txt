cmake_minimum_required(VERSION 3.10)
project(CrosswordSolver)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(--coverage)
add_link_options(--coverage)
add_library(CrosswordSolver STATIC source/CrosswordSolver.cpp)
target_include_directories(CrosswordSolver PUBLIC include)