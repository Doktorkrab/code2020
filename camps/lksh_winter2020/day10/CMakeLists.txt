cmake_minimum_required(VERSION 3.17)
project(day10)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-O0 -g3)
add_compile_definitions(_GLIBCXX_DEBUG)
add_executable(a src/a.cpp)
add_executable(gen src/gen.cpp)
