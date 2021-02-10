cmake_minimum_required(VERSION 3.17)
project(suff_automaton)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-O0 -g3)
add_executable(g src/g.cpp)
add_executable(h src/h.cpp)
