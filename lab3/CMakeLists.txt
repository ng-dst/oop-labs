cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 17)

project(lab3)

include_directories(lib)
include_directories(test)

add_library(libtable STATIC lib/OrderedTable.cpp)

add_executable(lab3 main.cpp)
target_link_libraries(lab3 libtable)
