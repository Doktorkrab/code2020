cmake_minimum_required(VERSION 3.17)
project(dist_tour1)

set(CMAKE_CXX_STANDARD 17)

add_executable(dist_tour1 main.cpp)
add_executable(a a.cpp)

add_executable(b_slow b_slow.cpp)

add_executable(b b.cpp)

add_executable(gen gen.cpp)