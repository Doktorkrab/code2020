cmake_minimum_required(VERSION 3.17)
project(day2)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-O0 -g3)
add_executable(f f.cpp)

add_executable(h h.cpp)

add_executable(j j.cpp)

add_executable(g g.cpp)

add_executable(j_slow check.cpp)

add_executable(gen gen.cpp)

add_executable(d d.cpp)

add_executable(i i.cpp)

add_executable(c c.cpp)

add_executable(h_slow h_slow.cpp)
