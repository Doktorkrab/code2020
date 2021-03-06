cmake_minimum_required(VERSION 3.17)
project(dist_tour7)

set(CMAKE_CXX_STANDARD 14)
add_compile_options(-O0 -g3)
add_executable(a src/a.cpp)
add_executable(b src/b.cpp)
add_executable(c src/c.cpp)
add_executable(d src/d.cpp)

add_executable(b_11 src/b_11.cpp)

add_executable(gen src/gen.cpp)
