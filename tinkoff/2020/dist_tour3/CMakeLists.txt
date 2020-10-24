cmake_minimum_required(VERSION 3.17)
project(dist_tour3)

set(CMAKE_CXX_STANDARD 17)

add_executable(dist_tour3 main.cpp)
add_executable(a a.cpp)

add_executable(a_slow a_slow.cpp)

add_executable(b b.cpp)

add_executable(b_slow b_slow.cpp)

add_executable(gen gen.cpp)

add_executable(c c.cpp)

add_executable(d d.cpp)

add_executable(d_slow d_slow.cpp)

add_executable(c_fast c_fast.cpp)
