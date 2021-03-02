cmake_minimum_required(VERSION 3.17)
project(graphs2)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-O0 -g3)
add_executable(graphs2 main.cpp)
add_executable(h src/h.cpp)

add_executable(a src/a.cpp)

add_executable(b src/b.cpp)
