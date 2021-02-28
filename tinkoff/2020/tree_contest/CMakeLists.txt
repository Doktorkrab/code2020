cmake_minimum_required(VERSION 3.17)
project(tree_contest)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-O0 -g3)
add_executable(n src/n.cpp)

add_executable(b src/b.cpp)

add_executable(c src/c.cpp)

add_executable(c_slow src/c_slow.cpp)

add_executable(gen src/gen.cpp)

add_executable(e src/e.cpp)

add_executable(a src/a.cpp)

add_executable(a_slow src/a_slow.cpp)

add_executable(l src/l.cpp)

add_executable(h src/h.cpp)

add_executable(h_slow src/h_slow.cpp)

add_executable(g src/g.cpp)

add_executable(m src/m.cpp)

add_executable(m1 src/m1.cpp)
