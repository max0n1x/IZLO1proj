cmake_minimum_required(VERSION 3.23)
project(projekt1_kostra C)

set(CMAKE_C_STANDARD 11)

include_directories(code)

add_executable(projekt1_kostra
        code/add_conditions.c
        code/cnf.h
        code/main.c)
