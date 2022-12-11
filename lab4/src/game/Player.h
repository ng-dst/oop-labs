/**
 * @file Player.h
 * Class for player entity containing his skills and abilities.
 */

#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H

#include <map>
#include <optional>

#include "Entity.h"
#include "Level.h"
#include "Mob.h"
#include "RangeCalc.h"
#include "TalentConfig.h"
#include "enum/Talent.h"
#include "enum/EntityType.h"
#include "enum/UndeadType.h"

using namespace std;

namespace DungeonGame {

    class Level;

    /**
     * Main entity controllable by player
     */
    class Player: public Entity {
        uint max_mana; /**< max Mana, increases with level, similar to HP */
        uint mana; /**< current Mana */
        uint exp; /**< current EXP */
        uint level; /**< player level, increased with EXP hitting threshold */
        map<Talent, uint>& talents; /**< map: talent type -> talent level */
        uint talent_points; /**< amount of points that player can use to upgrade talent levels */
        TalentConfig& talent_config; /**< struct containing constants that talents use */
        uint servant_count; /**< current amount of Undead servants that Player has spawned */

    public:
        Player(pair<uint, uint> pos,
               uint max_hp,
               uint atk,
               Fraction fraction,
               uint max_mana,
               uint exp,
               uint level,
               map<Talent, uint>& talents,
               uint talent_points,
               TalentConfig& talent_config);
        ~Player();

        [[nodiscard]] uint getMana() const;
        void setMana(uint mana);

        [[nodiscard]] uint getMaxMana() const;
        void setMaxMana(uint mana);

        [[nodiscard]] uint getExp() const;
        void setExp(uint xp);

        /**
         * Increase player's EXP, upgrading player level on thresholds
         *
         * @param dexp - value of gained EXP
         */
        void incExp(uint dexp);
        [[nodiscard]] uint getLevel() const;
        void setLevel(uint lvl);

        [[nodiscard]] uint getTalentPoints() const;
        void setTalentPoints(uint points);

        [[nodiscard]] uint getTalentLevel(Talent) const;
        void setTalentLevel(Talent, uint level);

        [[nodiscard]] uint getServantCount() const;
        void setServantCount(uint count);

        [[nodiscard]] const TalentConfig& getTalentConfig() const;

        /**
         * Apply player skill - Necromancy, on victim
         *
         * When facing a dead Mortal, turns them into Undead with player's fraction.
         * Requires mana (upgradable cost, set in Talent Config)
         * Each Undead type requires respective talent level to apply skill
         *
         *
         * @param victim - reference to dead (0 HP) Mortal mob
         * @param type - desired Undead type
         * @return pointer to summoned mob, if successful; nullptr otherwise.
         */
        Mob* applyNecromancy(Mob& victim, UndeadType type);

        /**
         * Apply player skill - Morphism, on victim
         *
         * When facing an Undead, transforms them into other Undead type
         * Requires mana (upgradable cost, set in Talent Config)
         * Both Undead types require respective talent level to apply skill
         *
         *
         * @param victim - an Undead (any fraction)
         * @param type - desired type
         * @return pointer to the same mob (victim), if successful; nullptr, otherwise
         */
        Mob* applyMorphism(Mob& victim, UndeadType type);

        /**
         * Apply player skill - Curse, AoE damage (directed)
         *
         * Deals AoE damage to enemies in player's facing direction
         * within a certain range (constant range, set in Talent Config)
         * Damage is upgradable and uses base ATK, with a multiplier set in Talent Config
         * Requires mana (constant cost, set in Talent Config)
         *
         *
         * @param field - current Level
         * @return true / false, whether applied successfully
         */
        bool applyCurse(Level& field);

        /**
         * Apply player skill - Ultimate, AoE damage (undirected)
         *
         * Deals large AoE damage to all surrounding enemies
         * within a certain range (constant range, set in Talent Config)
         * Damage is upgradable and uses base ATK, with a multiplier set in Talent Config
         *
         *
         * @param field - current Level
         * @return true / false, whether applied successfully
         */
        bool applyUltimate(Level& field);

        [[nodiscard]] EntityType getType() const override;

    private:
        bool _aoeDmg(Level& field, Talent type);

    };

}

#endif //OOP_PLAYER_H
