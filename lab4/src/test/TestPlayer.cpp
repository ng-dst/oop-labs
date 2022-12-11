#include "../../Google_tests/lib/googletest/include/gtest/gtest.h"

#include "Player.h"

#define PATH "/home/pacan/Desktop/C/labs/oop/lab4/levels/t_corpus"
#define CONFIG_FILE "/config.ini"
#define LEVEL_CONFIG_FILE "/level0.ini"
#define LEVEL_MAP_FILE "/level0_map.txt"


DungeonGame::Player createPlayer() {
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


TEST (PlayerTest, IncExp) {
    auto p = createPlayer();
    p.incExp(90);
    ASSERT_EQ(1, p.getLevel());
    ASSERT_EQ(90, p.getExp());
    ASSERT_EQ(0, p.getTalentPoints());
    p.incExp(15);
    ASSERT_EQ(2, p.getLevel());
    ASSERT_EQ(5, p.getExp());
    ASSERT_EQ(1, p.getTalentPoints());
}

TEST (PlayerTest, IncTalent) {
    auto p = createPlayer();
    p.incExp(210);
    ASSERT_EQ(2, p.getTalentPoints());
    p.setTalentLevel(DungeonGame::CURSE, p.getTalentLevel(DungeonGame::CURSE) + 1);
    p.setTalentPoints(p.getTalentPoints() - 1);
    p.setTalentLevel(DungeonGame::NECROMANCY, p.getTalentLevel(DungeonGame::NECROMANCY) + 1);
    p.setTalentPoints(p.getTalentPoints() - 1);

    ASSERT_EQ(p.getTalentLevel(DungeonGame::CURSE), 2);
    ASSERT_EQ(p.getTalentLevel(DungeonGame::NECROMANCY), 2);
}


TEST (PlayerTest, PlayerType) {
    auto p = createPlayer();
    ASSERT_EQ(DungeonGame::PLAYER, p.getType());
}