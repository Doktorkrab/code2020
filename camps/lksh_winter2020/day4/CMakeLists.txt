cmake_minimum_required(VERSION 3.17)
project(day4)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-O0 -g3)
add_executable(simplex src/simplex.cpp)

add_executable(simplex_positive src/simplex_positive.cpp)

add_executable(f src/f.cpp)

add_executable(f_slow src/f_slow.cpp)
add_executable(gen src/gen.cpp)
