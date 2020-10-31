cmake_minimum_required(VERSION 3.17)
project(data_structures)

set(CMAKE_CXX_STANDARD 17)

add_compile_definitions(LOCAL)
add_compile_options()
add_executable(data_structures main.cpp)
add_executable(a a.cpp)
add_compile_options(-O0 -g)
add_executable(c c.cpp)

add_executable(k k.cpp)

add_executable(d d.cpp)

add_executable(e e.cpp)

add_executable(b b.cpp)

add_executable(b_slow b_slow.cpp)

add_executable(gen gen.cpp)

add_executable(j j.cpp)

add_executable(i i.cpp)

add_executable(i1 i_slow.cpp)
add_executable(f f.cpp)

add_executable(q q.cpp)
