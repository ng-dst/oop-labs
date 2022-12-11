/**
 * @file TalentConfig.h
 * Struct with numeric constants defining player's Talents behavior.
 */

#ifndef OOP_TALENTCONFIG_H
#define OOP_TALENTCONFIG_H

#include <iostream>
#include <map>

#include "enum/UndeadType.h"

#include "../lib/simpleini/SimpleIni.h"


namespace DungeonGame {

    /**
     * Struct with numeric constants used by player's Talents.
     */
    struct TalentConfig {
        uint PlayerMaxHpAffix;
        uint PlayerMaxManaAffix;
        uint PlayerAtkAffix;
        uint ExpPerLevel;

        uint CurseMaxLevel;
        float CurseDmgBase;
        float CurseDmgAffix;
        uint CurseRange;
        uint CurseCost;

        uint WitheringMaxLevel;
        float WitheringHpBase;
        float WitheringHpAffix;
        uint WitheringManaBase;
        uint WitheringManaAffix;

        uint NecromancyMaxLevel;
        std::map<UndeadType, uint> NecromancyRequiredLevels;
        uint NecromancyCostBase;
        uint NecromancyCostAffix;
        uint NecromancyMaxServantsBase;
        uint NecromancyMaxServantsAffix;

        uint MorphismMaxLevel;
        uint MorphismCostBase;
        uint MorphismCostAffix;
        std::map<UndeadType, float> MorphismAtkMul;
        std::map<UndeadType, uint> MorphismRanges;

        uint UltimateMaxLevel;
        float UltimateDmgBase;
        float UltimateDmgAffix;
        uint UltimateRange;
        uint UltimateCost;
    };

    /**
     * load config from CSimpleIni object of world config file
     *
     * @param ini - CSimpleIni from world config file
     * @return reference to newly loaded talent config
     */
    TalentConfig& loadTalentConfig(CSimpleIniA& ini);

}

#endif //OOP_TALENTCONFIG_H
