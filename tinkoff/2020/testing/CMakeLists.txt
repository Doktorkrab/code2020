cmake_minimum_required(VERSION 3.17)
project(testing)

set(CMAKE_CXX_STANDARD 17)

add_executable(testing main.cpp)
add_executable(f f.cpp)

add_executable(g g.cpp)

add_executable(h h.cpp)

add_executable(k k.cpp)
