cmake_minimum_required(VERSION 3.17)
project(dist_tour4)

set(CMAKE_CXX_STANDARD 17)

add_executable(dist_tour4 main.cpp)
add_executable(a a.cpp)

add_executable(b b.cpp)

add_executable(c c.cpp)

add_executable(c_slow c_slow.cpp)

add_executable(gen gen.cpp)

add_executable(c1 c1.cpp)

add_executable(d d.cpp)
