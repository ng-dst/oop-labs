cmake_minimum_required(VERSION 3.17)
project(lab1)

set(CMAKE_CXX_STANDARD 17)

add_library(list list.cpp list.h)
add_library(spmatrix spmatrix.cpp spmatrix.h)
add_executable(lab1 main.cpp ../utils/input.h)

target_link_libraries(lab1 spmatrix list)