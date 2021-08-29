cmake_minimum_required(VERSION 3.17)
project(roi2021)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-O0 -g3)
add_executable(roi2021 main.cpp)
add_executable(b2 src/b2.cpp)
