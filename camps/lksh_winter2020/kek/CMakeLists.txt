cmake_minimum_required(VERSION 3.17)
project(kek)

set(CMAKE_CXX_STANDARD 17)

add_executable(kek main.cpp)
add_executable(e src/e.cpp)

add_executable(n src/n.cpp)
add_executable(code src/code.cpp)
add_executable(hashset src/hashset.cpp)

add_executable(code_inception src/code_inception.cpp)

add_executable(kirk src/kirk.cpp)
