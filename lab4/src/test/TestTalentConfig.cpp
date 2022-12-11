#include "../../Google_tests/lib/googletest/include/gtest/gtest.h"

#include "TalentConfig.h"

#define PATH "/home/pacan/Desktop/C/labs/oop/lab4/levels/t_corpus"
#define CONFIG_FILE "/config.ini"
#define LEVEL_CONFIG_FILE "/level0.ini"
#define LEVEL_MAP_FILE "/level0_map.txt"

TEST (TalentConfigTest, LoadTalentConfig) {
    CSimpleIniA ini;
    SI_Error rc = ini.LoadFile(PATH CONFIG_FILE);
    ASSERT_EQ(0, rc);
    DungeonGame::TalentConfig& tc = DungeonGame::loadTalentConfig(ini);

    ASSERT_EQ(tc.PlayerMaxHpAffix, 20);
    ASSERT_EQ(tc.CurseMaxLevel, 5);
    ASSERT_NEAR(tc.CurseDmgBase, 0.80, 1e-4);
    ASSERT_EQ(tc.NecromancyRequiredLevels.at(DungeonGame::SKELETON), 2);
    ASSERT_EQ(tc.NecromancyRequiredLevels.at(DungeonGame::ZOMBIE), 1);
    ASSERT_NEAR(tc.MorphismAtkMul.at(DungeonGame::GHOUL), 2.5, 1e-4);

    delete &tc;
}
