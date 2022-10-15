# 'Google_test' is the subproject name
project(Google_tests)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# 'Google_Tests_run' is the target name

include_directories(../lab2/lib)
add_executable(Google_Tests_run_lab2 ../lab2/test/test.cpp)
target_link_libraries(Google_Tests_run_lab2 gtest gtest_main libbooth)

include_directories(../lab3/lib)
add_executable(Google_Tests_run_lab3_static ../lab3/test/test_static.cpp ../lab3/lib/static/OrderedTable.h)
target_link_libraries(Google_Tests_run_lab3_static gtest gtest_main libtable)
add_executable(Google_Tests_run_lab3_overloaded ../lab3/test/test_overloaded.cpp ../lab3/lib/overloaded/OrderedTable.h)
target_link_libraries(Google_Tests_run_lab3_overloaded gtest gtest_main libtable)

#  3.c coming soon...
