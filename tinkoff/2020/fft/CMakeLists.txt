cmake_minimum_required(VERSION 3.17)
project(fft)

set(CMAKE_CXX_STANDARD 14)

add_executable(fft fft.cpp)
add_compile_options(-O0 -g3)
add_executable(gen gen.cpp)

add_executable(d d.cpp)

add_executable(b b.cpp)

add_executable(c c.cpp)
add_executable(kek kek.cpp)
