cmake_minimum_required(VERSION 3.17)
project(roi2019_2)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-O0 -g3)
add_executable(roi2019_2 main.cpp)
add_executable(a src/a.cpp)
add_executable(a_slow src/a_slow.cpp)
add_executable(gen src/gen.cpp)
add_executable(b src/b.cpp)

add_executable(c src/c.cpp)

add_executable(d src/d.cpp)

add_executable(b_lr src/b_lr.cpp)

add_executable(d1 src/d1.cpp)
