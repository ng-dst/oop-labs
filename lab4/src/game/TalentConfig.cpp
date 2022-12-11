#include "TalentConfig.h"

namespace DungeonGame {

    TalentConfig &loadTalentConfig(CSimpleIniA &ini) {
        TalentConfig& tc = *new TalentConfig();
        tc.PlayerMaxHpAffix = ini.GetLongValue("Player", "PlayerMaxHpAffix");
        tc.PlayerMaxManaAffix = ini.GetLongValue("Player", "PlayerMaxManaAffix");
        tc.PlayerAtkAffix = ini.GetLongValue("Player", "PlayerAtkAffix");
        tc.ExpPerLevel = ini.GetLongValue("Player", "ExpPerLevel");

        tc.CurseMaxLevel = ini.GetLongValue("Talents", "CurseMaxLevel");
        tc.CurseDmgBase = (float) ini.GetDoubleValue("Talents", "CurseDmgBase");
        tc.CurseDmgAffix = (float) ini.GetDoubleValue("Talents", "CurseDmgAffix");
        tc.CurseRange = ini.GetLongValue("Talents", "CurseRange");
        tc.CurseCost = ini.GetLongValue("Talents", "CurseCost");

        tc.WitheringMaxLevel = ini.GetLongValue("Talents", "WitheringMaxLevel");
        tc.WitheringHpBase = (float) ini.GetDoubleValue("Talents", "WitheringHpBase");
        tc.WitheringHpAffix = (float) ini.GetDoubleValue("Talents", "WitheringHpAffix");
        tc.WitheringManaBase = ini.GetLongValue("Talents", "WitheringManaBase");
        tc.WitheringManaAffix = ini.GetLongValue("Talents", "WitheringManaAffix");

        tc.NecromancyMaxLevel = ini.GetLongValue("Talents", "NecromancyMaxLevel");
        tc.NecromancyCostBase = ini.GetLongValue("Talents", "NecromancyCostBase");
        tc.NecromancyCostAffix = ini.GetLongValue("Talents", "NecromancyCostAffix");
        tc.NecromancyMaxServantsBase = ini.GetLongValue("Talents", "NecromancyMaxServantsBase");
        tc.NecromancyMaxServantsAffix = ini.GetLongValue("Talents", "NecromancyMaxServantsAffix");

        tc.NecromancyRequiredLevels[UndeadType::ZOMBIE] = ini.GetLongValue("Talents", "NecromancyZombieLevel");
        tc.NecromancyRequiredLevels[UndeadType::SKELETON] = ini.GetLongValue("Talents", "NecromancySkeletonLevel");
        tc.NecromancyRequiredLevels[UndeadType::VAMPIRE] = ini.GetLongValue("Talents", "NecromancyVampireLevel");
        tc.NecromancyRequiredLevels[UndeadType::GHOUL] = ini.GetLongValue("Talents", "NecromancyGhoulLevel");

        tc.MorphismMaxLevel = ini.GetLongValue("Talents", "MorphismMaxLevel");
        tc.MorphismCostBase = ini.GetLongValue("Talents", "MorphismCostBase");
        tc.MorphismCostAffix = ini.GetLongValue("Talents", "MorphismCostAffix");

        tc.MorphismAtkMul[UndeadType::ZOMBIE] = (float) ini.GetDoubleValue("Talents", "MorphismZombieAtk", 1.0);
        tc.MorphismAtkMul[UndeadType::SKELETON] = (float) ini.GetDoubleValue("Talents", "MorphismSkeletonAtk", 1.0);
        tc.MorphismAtkMul[UndeadType::VAMPIRE] = (float) ini.GetDoubleValue("Talents", "MorphismVampireAtk", 1.0);
        tc.MorphismAtkMul[UndeadType::GHOUL] = (float) ini.GetDoubleValue("Talents", "MorphismGhoulAtk", 1.0);
        tc.MorphismRanges[UndeadType::ZOMBIE] = ini.GetLongValue("Talents", "MorphismZombieRange");
        tc.MorphismRanges[UndeadType::SKELETON] = ini.GetLongValue("Talents", "MorphismSkeletonRange");
        tc.MorphismRanges[UndeadType::VAMPIRE] = ini.GetLongValue("Talents", "MorphismVampireRange");
        tc.MorphismRanges[UndeadType::GHOUL] = ini.GetLongValue("Talents", "MorphismGhoulRange");

        tc.UltimateMaxLevel = ini.GetLongValue("Talents", "UltimateMaxLevel");
        tc.UltimateDmgBase = (float) ini.GetDoubleValue("Talents", "UltimateDmgBase");
        tc.UltimateDmgAffix = (float) ini.GetDoubleValue("Talents", "UltimateDmgAffix");
        tc.UltimateRange = ini.GetLongValue("Talents", "UltimateRange");
        tc.UltimateCost = ini.GetLongValue("Talents", "UltimateCost");

        return tc;
    }

}