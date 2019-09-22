cmake_minimum_required(VERSION 3.14)
project(learning_c C)

set(CMAKE_C_STANDARD 11)

add_executable(learning_c src/main.c src/array.h src/array.c src/extvars.c src/extvars.h src/printing.c src/printing.h)