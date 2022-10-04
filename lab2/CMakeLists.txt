cmake_minimum_required(VERSION 3.17)
project(lab2)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)
include_directories(test)

add_library(booth src/LemniscateBooth.cpp)

add_executable(lab2 main.cpp)
target_link_libraries(lab2 booth)
