#include "Mob.h"

namespace DungeonGame {

    bool Mob::isSpawner() const { return is_spawner; }
    void Mob::setSpawner(bool spawner) {
        if (spawner && getType() == GOLEM)
            throw std::logic_error("setSpawner: Golems can't spawn mobs");
        is_spawner = spawner;
    }

    UndeadType Mob::getSpawnType() const { return spawn_type; }
    void Mob::setSpawnType(UndeadType undead_type) { spawn_type = undead_type; }

    uint Mob::getAtkRange() const { return atk_range; }
    void Mob::setAtkRange(uint range) { atk_range = range; }

    uint Mob::getVisRange() const { return vis_range; }
    void Mob::setVisRange(uint range) { vis_range = range; }

    const std::string& Mob::getName() const { return name; }
    void Mob::setName(const std::string& new_name) { name = new_name; }

    uint Mob::getSpeed() const { return speed; }
    void Mob::setSpeed(uint new_speed) { speed = new_speed; }

}
