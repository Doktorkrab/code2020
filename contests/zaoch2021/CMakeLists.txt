cmake_minimum_required(VERSION 3.17)
project(zaoch2021)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-O0 -g3)
add_executable(zaoch2021 src/main.cpp)
add_executable(a src/a.cpp)

add_executable(src/gen.cpp)

add_executable(src/c.cpp)

add_executable(b2 src/b2.cpp)
add_executable(src/c_19.cpp)

add_executable(d_19 src/d_19.cpp)

add_executable(d src/d.cpp)

add_executable(e src/e.cpp)
