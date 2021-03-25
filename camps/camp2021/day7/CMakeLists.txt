cmake_minimum_required(VERSION 3.17)
project(day7)

set(CMAKE_CXX_STANDARD 17)

#add_compile_options(-O0 -g3)
add_executable(a src/a.cpp)

add_executable(b src/b.cpp)

add_executable(b_slow src/b_slow.cpp)

add_executable(c src/c.cpp)

add_executable(d src/d.cpp)
add_executable(d_denchik src/d_denchik.cpp)
