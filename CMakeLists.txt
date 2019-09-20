cmake_minimum_required(VERSION 3.14)
project(arrays C)

set(CMAKE_C_STANDARD 11)

add_executable(arrays src/main.c src/array.h src/array.c src/extvars.c src/extvars.h)