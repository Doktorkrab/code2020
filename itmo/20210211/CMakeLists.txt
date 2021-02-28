cmake_minimum_required(VERSION 3.17)
project(20210211)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-O0 -g3)
add_executable(20210211 main.cpp)
add_executable(a src/a.cpp)

add_executable(b src/b.cpp)

add_executable(e src/e.cpp)

add_executable(f src/f.cpp)

add_executable(i src/i.cpp)

add_executable(g src/g.cpp)

add_executable(h src/h.cpp)

add_executable(h1 src/h1.cpp)
add_executable(gen src/gen.cpp)
