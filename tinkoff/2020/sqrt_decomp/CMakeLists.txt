cmake_minimum_required(VERSION 3.17)
project(sqrt_decomp)

set(CMAKE_CXX_STANDARD 17)

add_compile_definitions(_GLIBCXX_DEBUG)
add_compile_definitions(_GLIBCXX_DEBUG_PEDANTIC)
add_executable(sqrt_decomp main.cpp)
add_executable(l l.cpp)

add_executable(d d.cpp)

add_executable(c c.cpp)

add_executable(f f.cpp)

add_executable(gen gen.cpp)
add_executable(g g.cpp)

add_executable(b b.cpp)

add_executable(i i.cpp)
