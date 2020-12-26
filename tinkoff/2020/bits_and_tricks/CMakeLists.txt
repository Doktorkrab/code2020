cmake_minimum_required(VERSION 3.17)
project(bits_and_tricks)
add_compile_options(-O0 -g3)
set(CMAKE_CXX_STANDARD 17)

add_executable(bits_and_tricks src/main.cpp)
add_executable(e src/e.cpp)

add_executable(h src/h.cpp)

add_executable(b src/b.cpp)

add_executable(c src/c.cpp)

add_executable(d src/d.cpp)

add_executable(f src/f.cpp)
