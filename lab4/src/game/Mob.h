/**
 * @file Mob.h
 * Intermediate class for AI-controlled mobs.
 */

#ifndef OOP_MOB_H
#define OOP_MOB_H

#include "Entity.h"
#include "enum/UndeadType.h"

namespace DungeonGame {

    /**
     * Extension of base class for AI-controlled mobs on level
     */
    class Mob: public Entity {
    protected:
        bool is_spawner; /**< indicates if the mob is Spawner, i.e. can spawn other mobs */
        UndeadType spawn_type; /**< undead type of spawned mobs (if is_spawner is true) */
        std::string name; /**< string name of the mob */
        uint atk_range; /**< range in which mob can use normal attacks */
        uint vis_range; /**< range in which mob can see enemies and move towards them */
        uint speed; /**< amount of move attempts (probability of move: Level.move_prob) */

    public:
        [[nodiscard]] bool isSpawner() const;
        void setSpawner(bool spawner);

        [[nodiscard]] UndeadType getSpawnType() const;
        void setSpawnType(UndeadType undead_type);

        [[nodiscard]] uint getAtkRange() const;
        void setAtkRange(uint range);

        [[nodiscard]] uint getVisRange() const;
        void setVisRange(uint range);

        [[nodiscard]] const std::string& getName() const;
        void setName(const std::string& name);

        [[nodiscard]] uint getSpeed() const;
        void setSpeed(uint speed);

    };

}

#endif //OOP_MOB_H
