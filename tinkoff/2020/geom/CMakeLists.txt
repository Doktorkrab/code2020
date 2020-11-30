cmake_minimum_required(VERSION 3.17)
project(geom)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-O0 -g3)
#add_compile_definitions(_GLIBCXX_DEBUG)
add_executable(a a.cpp)

add_executable(b b.cpp)

add_executable(f f.cpp)

add_executable(p p.cpp)

add_executable(d d.cpp)

add_executable(c c.cpp)

add_executable(l l.cpp)

add_executable(g g.cpp)

add_executable(n n.cpp)
