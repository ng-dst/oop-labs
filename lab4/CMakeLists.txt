cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 17)

project(lab4)

set(G_DIR src/game)
set(SIMPLE_INI_DIR src/lib/simpleini)

include_directories(src/graphics)
include_directories(${G_DIR})
include_directories(${G_DIR}/mobs)
include_directories(${SIMPLE_INI_DIR})

add_library(dungeon ${G_DIR}/Level.cpp ${G_DIR}/RangeCalc.cpp ${G_DIR}/World.cpp ${G_DIR}/TalentConfig.cpp
                             ${G_DIR}/Entity.cpp ${G_DIR}/Player.cpp ${G_DIR}/Mob.cpp
                             ${G_DIR}/mobs/Golem.cpp ${G_DIR}/mobs/Mortal.cpp ${G_DIR}/mobs/Undead.cpp)

add_library(simple-ini ${SIMPLE_INI_DIR}/ConvertUTF.c ${SIMPLE_INI_DIR}/ConvertUTF.h ${SIMPLE_INI_DIR}/SimpleIni.h)

add_executable(lab4 src/main.cpp src/graphics/TileMap.cpp)
include_directories(src/test)

target_link_libraries(lab4 dungeon)
target_link_libraries(lab4 simple-ini)
target_link_libraries(lab4 sfml-graphics sfml-window sfml-system)
