cmake_minimum_required(VERSION 3.17)
project(suff_automaton)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-O0 -g3)
add_executable(g src/g.cpp)
add_executable(h src/h.cpp)

add_executable(b src/b.cpp)
add_executable(gen src/gen.cpp)
add_executable(f src/f.cpp)
