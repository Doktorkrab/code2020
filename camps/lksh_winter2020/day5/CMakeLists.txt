cmake_minimum_required(VERSION 3.17)
project(day5)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-O0 -g3)
add_executable(suffAuto src/suffAuto.cpp)

add_executable(b_stress src/b_stress.cpp)
add_executable(gen src/gen.cpp)

add_executable(c src/c.cpp)

add_executable(e src/e.cpp)
