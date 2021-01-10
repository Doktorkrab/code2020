cmake_minimum_required(VERSION 3.17)
project(day8_number)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-O0 -g3)
add_executable(day8_number main.cpp)
add_executable(c src/c.cpp)

add_executable(f src/f.cpp)

add_executable(a src/a.cpp)

add_executable(b src/b.cpp)
