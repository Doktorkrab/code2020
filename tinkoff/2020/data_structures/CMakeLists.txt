cmake_minimum_required(VERSION 3.17)
project(data_structures)

set(CMAKE_CXX_STANDARD 17)

add_compile_definitions(LOCAL)
add_executable(data_structures main.cpp)
add_executable(a a.cpp)
add_compile_options(-O0 -g)
add_executable(c c.cpp)

add_executable(n n.cpp)
