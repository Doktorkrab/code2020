cmake_minimum_required(VERSION 3.19)
project(august_clion)

set(CMAKE_CXX_STANDARD 17)

add_executable(august_clion main.cpp)
add_executable(dijkstra_without_heap src/dijkstra_without_heap.cpp)
add_executable(kek src/kek.cpp)