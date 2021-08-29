cmake_minimum_required(VERSION 3.19)
project(made_contest)

set(CMAKE_CXX_STANDARD 17)

add_executable(made_contest main.cpp)
add_executable(a src/a.cpp)
add_executable(b src/b.cpp)
add_executable(c src/c.cpp)
add_executable(d src/d.cpp)
add_executable(e src/e.cpp)

add_executable(a1 src/a1.cpp)

add_executable(f2 src/f2.cpp)

add_executable(d_slow src/d_slow.cpp)

add_executable(gen src/gen.cpp)
