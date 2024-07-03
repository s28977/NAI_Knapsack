cmake_minimum_required(VERSION 3.28)
project(NAI_Knapsack C)

set(CMAKE_C_STANDARD 23)

add_executable(BruteForce src/brute_force.c)
add_executable(Dynamic src/dynamic_programming.c)
