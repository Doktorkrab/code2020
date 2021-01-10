cmake_minimum_required(VERSION 3.17)
project(day2)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-O0 -g3)
#add_compile_options(-O2)
#add_compile_options(-g -Wall -Wextra -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -Wconversion -lm -fsanitize=address -fsanitize=bounds -Wshadow -D_FORTIFY_SOURCE=2 -fsanitize=undefined -fno-sanitize-recover -Wformat=2 -fno-stack-limit)
add_executable(gen src/gen.cpp)
add_executable(f src/f.cpp)

add_executable(c src/c.cpp)

add_executable(e src/e.cpp)

add_executable(a src/a.cpp)

add_executable(a_slow src/a_slow.cpp)

add_executable(g src/g.cpp)

add_executable(b src/b.cpp)
