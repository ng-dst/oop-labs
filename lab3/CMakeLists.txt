cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 17)

# -------------------------------- Uncomment desired version here -------------------------------- #
#set(LAB_VARIANT "static")
#set(LAB_VARIANT "overloaded")
set(LAB_VARIANT "dynamic")
# ------------------------------------------------------------------------------------------------ #

project(lab3)
include_directories(lib)

include_directories(lib/${LAB_VARIANT})
add_library(libtable STATIC lib/${LAB_VARIANT}/OrderedTable.cpp)

include_directories(test)

add_executable(lab3 main.cpp)
target_link_libraries(lab3 libtable)
