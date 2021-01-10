cmake_minimum_required(VERSION 3.17)
project(zaoch2021_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(e src/e.cpp)
add_compile_options(-O0 -g3)
add_executable(f src/f.cpp)
add_executable(gen src/gen.cpp)

add_executable(f1 src/f1.cpp)
