/**
 * @file Undead.h
 * Undead class
 */

#ifndef OOP_UNDEAD_H
#define OOP_UNDEAD_H

#include "Mortal.h"
#include "../Mob.h"
#include "../enum/EntityType.h"
#include "../enum/UndeadType.h"

namespace DungeonGame {

    /**
     * Undead - type of mob
     *
     * There are 4 types of Undeads, each one has its own parameters.
     * Undeads can be transformed to another Undead type with player's Morphism talent.
     *
     */
    class Undead: public Mob {
        UndeadType undead_type;

    public:
        Undead(std::pair<uint, uint> pos,
               uint max_hp,
               uint atk,
               float atk_range,
               float vis_range,
               int speed,
               Fraction fraction,
               const std::string& name,
               UndeadType type,
               bool is_spawner = false,
               UndeadType spawn_type = ZOMBIE);

        Undead(const Mortal& body, UndeadType new_type);

        [[nodiscard]] UndeadType getUndeadType() const;
        void setUndeadType(UndeadType type);

        [[nodiscard]] EntityType getType() const override;
    };

}

#endif //OOP_UNDEAD_H
