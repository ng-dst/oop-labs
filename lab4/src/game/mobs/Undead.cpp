#include "Undead.h"

namespace DungeonGame {

    Undead::Undead(std::pair<uint, uint> pos, uint max_hp, uint atk, float atk_range,
                   float vis_range, int speed, Fraction fraction, const std::string& name,
                   UndeadType und_type, bool is_spawner, UndeadType spawn_type) {
        this->pos = pos;
        this->max_hp = max_hp;
        this->cur_hp = max_hp;
        this->facing = LEFT;
        this->type = UNDEAD;
        this->atk = atk;
        this->atk_range = atk_range;
        this->vis_range = vis_range;
        this->speed = speed;
        this->fraction = fraction;
        this->name = name;
        this->undead_type = und_type;
        this->is_spawner = is_spawner;
        this->spawn_type = spawn_type;
    }

    UndeadType Undead::getUndeadType() const {
        return undead_type;
    }

    void Undead::setUndeadType(const UndeadType und_type) {
        undead_type = und_type;
    }

    EntityType Undead::getType() const {
        return UNDEAD;
    }

    Undead::Undead(const Mortal &body, UndeadType new_type) {
        undead_type = new_type;
        is_spawner = body.isSpawner();
        spawn_type = body.getSpawnType();
        facing = body.getFacing();
        type = UNDEAD;
        name = body.getName();
        atk_range = body.getAtkRange();
        vis_range = body.getVisRange();
        speed = body.getSpeed();
        pos = body.getPos();
        max_hp = body.getMaxHp();
        cur_hp = max_hp / 4 + 1;
        atk = body.getAtk();
        fraction = body.getFraction();
    }

}