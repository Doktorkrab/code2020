cmake_minimum_required(VERSION 3.17)
project(20201123)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-O0 -g3)
add_executable(a a.cpp)

add_executable(b b.cpp)

add_executable(c c.cpp)

add_executable(d d.cpp)
add_executable(e e.cpp)

add_executable(d_cube d_cube.cpp)

add_executable(gen gen.cpp)
