cmake_minimum_required(VERSION 3.17)
project(olymp)

set(CMAKE_CXX_STANDARD 17)
add_compile_definitions(_GLIBCXX_DEBUG)
add_compile_options(-O0 -g3)
add_executable(olymp main.cpp)
add_executable(gen gen.cpp)