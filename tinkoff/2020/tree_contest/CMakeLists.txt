cmake_minimum_required(VERSION 3.17)
project(tree_contest)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-O0 -g3)
add_executable(n n.cpp)

add_executable(b b.cpp)

add_executable(c c.cpp)

add_executable(c_slow c_slow.cpp)

add_executable(gen gen.cpp)

add_executable(e e.cpp)

add_executable(a a.cpp)

add_executable(a_slow a_slow.cpp)
