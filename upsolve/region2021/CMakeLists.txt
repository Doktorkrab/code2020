cmake_minimum_required(VERSION 3.17)
project(region2021)

set(CMAKE_CXX_STANDARD 17)

add_executable(region2021 main.cpp)
add_executable(d1 src/d1.cpp)
add_executable(gen src/gen.cpp)
add_executable(d_nb src/d_nb.cpp)
add_executable(d2 src/d2.cpp)

add_executable(c2 src/c2.cpp)
