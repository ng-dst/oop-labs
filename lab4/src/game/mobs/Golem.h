/**
 * @file Golem.h
 * Golem class
 */

#ifndef OOP_GOLEM_H
#define OOP_GOLEM_H

#include "../Mob.h"
#include "../enum/GolemElementType.h"
#include "../enum/EntityType.h"

namespace DungeonGame {

    /**
     * Golem - type of mob
     *
     * can have different elemental types, altering effects caused by their death,
     * can dodge enemy attacks with a set probability.
     *
     */
    class Golem: public Mob {
        GolemElementType golem_type; /**< elemental type of golem which sets a death effect */
        float dodge_prob; /**< in [0; 1], probability of attack dodge */

    public:
        Golem (std::pair<uint, uint> pos,
               uint max_hp,
               uint atk,
               uint atk_range,
               uint vis_range,
               uint speed,
               Fraction fraction,
               const std::string& name,
               GolemElementType type,
               float dodge_prob);

        [[nodiscard]] GolemElementType getGolemType() const;
        void setGolemType(GolemElementType type);

        [[nodiscard]] float getDodgeProb() const;
        void setDodgeProb(float prob);

        /**
         * overridden: try to dodge when taking damage
         * @param dmg
         */
        void damage(uint dmg) override;

        [[nodiscard]] EntityType getType() const override;
    };

}

#endif //OOP_GOLEM_H
