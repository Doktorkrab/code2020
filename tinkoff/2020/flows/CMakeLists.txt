cmake_minimum_required(VERSION 3.17)
project(flows)

set(CMAKE_CXX_STANDARD 17)

add_executable(flows main.cpp)
add_executable(a a.cpp)

add_executable(b b.cpp)

add_executable(f f.cpp)

add_executable(f_slow f_slow.cpp)
add_executable(gen gen.cpp)

add_executable(i i.cpp)

add_executable(j j.cpp)

add_executable(c c.cpp)

add_executable(k k.cpp)

add_executable(g g.cpp)
