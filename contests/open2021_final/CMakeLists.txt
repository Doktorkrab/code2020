cmake_minimum_required(VERSION 3.17)
project(open2021_final)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-O0 -g3)
add_executable(open2021_final main.cpp)
add_executable(party src/party.cpp)

add_executable(bukhalter src/bukhalter.cpp)

add_executable(winner src/winner.cpp)

add_executable(winner_slow src/winner_slow.cpp)
add_executable(gen src/gen.cpp)
add_executable(otvinta src/otvinta.cpp)

add_executable(bukhalter_fast src/bukhalter_fast.cpp)


add_executable(next_episode src/next_episode.cpp)

add_executable(wind_of_change src/wind_of_change.cpp)

add_executable(this_gonna_be_hurt src/this_gonna_be_hurt.cpp)

add_executable(champions src/champions.cpp)

add_executable(bukhalter_upsolve src/bukhalter_upsolve.cpp)

add_executable(next_episode_upsolve src/next_episode_upsolve.cpp)
