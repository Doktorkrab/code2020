cmake_minimum_required(VERSION 3.17)
project(day8)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-O0 -g3)
add_executable(a src/a.cpp)
add_executable(gen src/gen.cpp)
add_executable(a_slow src/a_slow.cpp)

add_executable(c src/c.cpp)
add_executable(c_fedor src/c_fedor.cpp)
