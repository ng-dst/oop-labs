/**
 * @file Mortal.h
 * Mortal class
 */

#ifndef OOP_MORTAL_H
#define OOP_MORTAL_H

#include "../Mob.h"
#include "../enum/EntityType.h"

namespace DungeonGame {

    /**
     * Mortal - type of mob
     *
     * Upon death, Mortals' bodies don't disappear, instead they give player EXP
     * Dead Mortals can be turned to Undeads with player's Necromancy talent.
     *
     */
    class Mortal: public Mob {
        uint exp; /**< amount of EXP given to the player for kill */

    public:
        Mortal(std::pair<uint, uint> pos,
               uint max_hp,
               uint atk,
               float atk_range,
               float vis_range,
               int speed,
               Fraction fraction,
               const std::string& name,
               uint exp,
               bool is_spawner = false,
               UndeadType spawn_type = ZOMBIE);

        [[nodiscard]] bool isAlive() const;

        [[nodiscard]] uint getExp() const;
        void setExp(uint exp);

        [[nodiscard]] EntityType getType() const override;
    };

}

#endif //OOP_MORTAL_H
