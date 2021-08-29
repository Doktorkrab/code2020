cmake_minimum_required(VERSION 3.17)
project(np)



set(CMAKE_CXX_STANDARD 20)

add_executable(np main.cpp)
find_library(CRYPTOMINISAT5_RELEASE cryptominisat5
        PATHS
        /usr/lib
        /usr/local/lib)

target_link_libraries(np ${CRYPTOMINISAT5_RELEASE})
add_executable(k src/k.cpp)

add_executable(l src/l.cpp)
