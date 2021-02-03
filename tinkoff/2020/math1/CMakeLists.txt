cmake_minimum_required(VERSION 3.17)
project(math1)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-O0 -g3)
add_executable(math1 main.cpp)
add_executable(a src/a.cpp)

add_executable(g src/g.cpp)

add_executable(n src/n.cpp)

add_executable(o src/o.cpp)
