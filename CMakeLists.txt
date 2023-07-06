cmake_minimum_required(VERSION 3.25)
project(AStarProject C)

set(CMAKE_C_STANDARD 11)

add_executable(AStarProject main.c src/algorithm/astar.h src/algorithm/algorithmUtils.h src/config.h src/libs/utils.h)
