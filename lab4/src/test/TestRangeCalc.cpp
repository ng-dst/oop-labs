#include "../../Google_tests/lib/googletest/include/gtest/gtest.h"

#include "RangeCalc.h"

#include "Player.h"
#include "Level.h"
#include "enum/Cell.h"

#define PATH "/home/pacan/Desktop/C/labs/oop/lab4/levels/t_corpus"
#define CONFIG_FILE "/config.ini"
#define LEVEL_CONFIG_FILE "/level0.ini"
#define LEVEL_MAP_FILE "/level0_map.txt"


TEST (RangeCalcTest, FindRange) {
    vector<vector<DungeonGame::Cell>> field;
    DungeonGame::Level::loadLevelMap(field, 12, 15, PATH LEVEL_MAP_FILE);
    DungeonGame::RangeCalc calc(field);

    ASSERT_EQ(10, calc.range(make_pair(7, 5), make_pair(1, 1)));
    ASSERT_EQ(8, calc.range(make_pair(7, 5), make_pair(6, 12)));
    ASSERT_EQ(20, calc.range(make_pair(11, 5), make_pair(0, 14)));

    ASSERT_EQ(-1, calc.range(make_pair(7, 5), make_pair(11, 0)));
    ASSERT_EQ(-1, calc.range(make_pair(11, 0), make_pair(10, 6)));
}


TEST (RangeCalcTest, FindRangeDirected) {
    vector<vector<DungeonGame::Cell>> field;
    DungeonGame::Level::loadLevelMap(field, 12, 15, PATH LEVEL_MAP_FILE);
    DungeonGame::RangeCalc calc(field);

    ASSERT_EQ(10, calc.range(make_pair(7, 5), make_pair(1, 1), true, DungeonGame::Direction::UP));
    ASSERT_EQ(-1, calc.range(make_pair(7, 5), make_pair(1, 1), true, DungeonGame::Direction::DOWN));
    ASSERT_EQ(-1, calc.range(make_pair(6, 11), make_pair(7, 12), true, DungeonGame::Direction::UP));
}


TEST (RangeCalcTest, FindPath) {
    vector<vector<DungeonGame::Cell>> field;
    DungeonGame::Level::loadLevelMap(field, 12, 15, PATH LEVEL_MAP_FILE);
    DungeonGame::RangeCalc calc(field);

    ASSERT_EQ(15, calc.path(make_pair(6,12), make_pair(2,1), 1, 25).size());
    ASSERT_EQ(0, calc.path(make_pair(6,12), make_pair(11,0), 1, 25).size());

}