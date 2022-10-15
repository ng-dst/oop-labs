cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 17)

project(lab3)
include_directories(lib)

# -------------------------------- Uncomment desired version here -------------------------------- #

# include_directories(lib/static)
include_directories(lib/overloaded)
# include_directories(lib/dynamic)

#add_library(libtable STATIC lib/static/OrderedTable.cpp)
add_library(libtable STATIC lib/overloaded/OrderedTable.cpp)
# add_library(libtable STATIC lib/dynamic/OrderedTable.cpp)

# ------------------------------------------------------------------------------------------------ #

include_directories(test)

add_executable(lab3 main.cpp)
target_link_libraries(lab3 libtable)
