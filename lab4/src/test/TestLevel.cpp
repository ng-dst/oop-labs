#include "../../Google_tests/lib/googletest/include/gtest/gtest.h"

#include "Level.h"
#include "Player.h"
#include "enum/Talent.h"

#define PATH "/home/pacan/Desktop/C/labs/oop/lab4/levels/t_corpus"
#define CONFIG_FILE "/config.ini"
#define LEVEL_CONFIG_FILE "/level0.ini"
#define LEVEL_MAP_FILE "/level0_map.txt"


DungeonGame::Player newPlayer() {
    map<DungeonGame::Talent, uint>& talents = *new map<DungeonGame::Talent, uint>();
    talents[DungeonGame::WITHERING] = 1;
    talents[DungeonGame::CURSE] = 1;
    talents[DungeonGame::NECROMANCY] = 1;
    talents[DungeonGame::MORPHISM] = 1;
    talents[DungeonGame::ULTIMATE] = 1;
    CSimpleIniA ini;
    ini.LoadFile(PATH CONFIG_FILE);
    DungeonGame::TalentConfig& tc = DungeonGame::loadTalentConfig(ini);
    return DungeonGame::Player(make_pair(0,0), 100, 40, DungeonGame::ALLIANCE, 80, 0, 1, talents, 0, tc);
}


TEST (LevelLoadTest, LoadLevelMap) {
    vector<vector<DungeonGame::Cell>> map;
    DungeonGame::Level::loadLevelMap(map, 12, 15, PATH LEVEL_MAP_FILE);

    ASSERT_EQ(DungeonGame::Cell::WALL, map[0][0]);
    ASSERT_EQ(DungeonGame::Cell::DOOR_OPEN, map[5][5]);
    ASSERT_EQ(DungeonGame::Cell::DOOR_CLOSED, map[9][14]);
    ASSERT_EQ(DungeonGame::Cell::WALL, map[11][11]);
}


TEST (LevelLoadTest, LevelLoadConfig) {
    DungeonGame::Player p = newPlayer();
    DungeonGame::Level lvl = DungeonGame::Level(PATH, 0, p);

    ASSERT_EQ(make_pair(12u, 15u), lvl.getMapSize());
    ASSERT_NE(nullptr, lvl.getMob(5, 10));
    ASSERT_EQ(60, lvl.getMob(5, 10)->getHp());
    auto* mob = (DungeonGame::Golem*) lvl.getMob(9, 9);
    ASSERT_NE(nullptr, mob);
    ASSERT_EQ(DungeonGame::GOLEM, mob->getType());
    ASSERT_EQ(DungeonGame::EXPLOSIVE, mob->getGolemType());
}


TEST (LevelMobsTest, LevelSpawnMob) {
    DungeonGame::Mortal& mob = *new DungeonGame::Mortal(make_pair(0,1), 100, 40,
                                                  3, 6, 1, DungeonGame::BANDITS,
                                                  "test subject", 35, true, DungeonGame::ZOMBIE);
    DungeonGame::Player p = newPlayer();
    DungeonGame::Level lvl = DungeonGame::Level(PATH, 0, p);

    ASSERT_TRUE(lvl.spawnMob(mob));
    ASSERT_EQ(4, lvl.getMobList().size());
    ASSERT_EQ(DungeonGame::BANDITS, lvl.getMobList().back()->getFraction());

    ASSERT_FALSE(lvl.spawnMob(mob)); // same pos
    ASSERT_EQ(4, lvl.getMobList().size());
}
