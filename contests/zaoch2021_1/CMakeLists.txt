cmake_minimum_required(VERSION 3.17)
project(zaoch2021_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(e src/e.cpp)
add_compile_options(-O0 -g3)
add_executable(f src/f.cpp)
add_executable(gen src/gen.cpp)

add_executable(f1 src/f1.cpp)


add_executable(h src/h.cpp)

add_executable(i src/i.cpp)

add_executable(i1 src/i1.cpp)

add_executable(g src/g.cpp)

add_executable(j src/j.cpp)
