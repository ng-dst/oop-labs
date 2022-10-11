cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 17)

project(lab2)

include_directories(lib)
include_directories(test)

add_library(libbooth STATIC lib/LemniscateBooth.cpp)

add_executable(lab2 main.cpp)
target_link_libraries(lab2 libbooth)
