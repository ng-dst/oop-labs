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
add_executable(Google_Tests_run_lab3_static ../lab3/test/test_static.cpp)
target_link_libraries(Google_Tests_run_lab3_static gtest gtest_main libtable)
add_executable(Google_Tests_run_lab3_overloaded ../lab3/test/test_overloaded.cpp)
target_link_libraries(Google_Tests_run_lab3_overloaded gtest gtest_main libtable)
add_executable(Google_Tests_run_lab3_dynamic ../lab3/test/test_overloaded.cpp)
target_link_libraries(Google_Tests_run_lab3_dynamic gtest gtest_main libtable)
target_compile_definitions(Google_Tests_run_lab3_dynamic PRIVATE DYNAMIC)

include_directories(../lab4/src/game)
add_executable(Google_Tests_run_lab4_world ../lab4/src/test/TestWorld.cpp)
target_link_libraries(Google_Tests_run_lab4_world gtest gtest_main dungeon)
add_executable(Google_Tests_run_lab4_calc ../lab4/src/test/TestRangeCalc.cpp)
target_link_libraries(Google_Tests_run_lab4_calc gtest gtest_main dungeon)
add_executable(Google_Tests_run_lab4_talent ../lab4/src/test/TestTalentConfig.cpp)
target_link_libraries(Google_Tests_run_lab4_talent gtest gtest_main dungeon)
add_executable(Google_Tests_run_lab4_player ../lab4/src/test/TestPlayer.cpp)
target_link_libraries(Google_Tests_run_lab4_player gtest gtest_main dungeon)
add_executable(Google_Tests_run_lab4_mobs ../lab4/src/test/TestMobs.cpp)
target_link_libraries(Google_Tests_run_lab4_mobs gtest gtest_main dungeon)
add_executable(Google_Tests_run_lab4_level ../lab4/src/test/TestLevel.cpp)
target_link_libraries(Google_Tests_run_lab4_level gtest gtest_main dungeon)
add_executable(Google_Tests_run_lab4 ../lab4/src/test/TestWorld.cpp ../lab4/src/test/TestRangeCalc.cpp
        ../lab4/src/test/TestTalentConfig.cpp ../lab4/src/test/TestPlayer.cpp
        ../lab4/src/test/TestMobs.cpp ../lab4/src/test/TestLevel.cpp)
target_link_libraries(Google_Tests_run_lab4 gtest gtest_main dungeon)

