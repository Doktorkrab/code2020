cmake_minimum_required(VERSION 3.17)
project(dp_optimizations)

set(CMAKE_CXX_STANDARD 17)

#add_compile_options(-g3 -O0)
add_executable(dp_optimizations main.cpp)
add_executable(a a.cpp)

add_executable(b b.cpp)

add_executable(c c.cpp)

add_executable(gen gen.cpp)

add_executable(test test.cpp)

add_executable(c_fast c_fast.cpp)

add_executable(f f.cpp)

add_executable(q q.cpp)

add_executable(m m.cpp)

add_executable(h h.cpp)

add_executable(e e.cpp)

add_executable(l l.cpp)

add_executable(e_slow.cpp e_slow.cpp)

add_executable(o o.cpp)
