#include "Mortal.h"

namespace DungeonGame {

    Mortal::Mortal(std::pair<uint, uint> pos, uint max_hp, uint atk, float atk_range,
                   float vis_range, int speed, Fraction fraction, const std::string& name, uint exp,
                   bool is_spawner, UndeadType spawn_type) {
        this->pos = pos;
        this->max_hp = max_hp;
        this->cur_hp = max_hp;
        this->facing = LEFT;
        this->type = MORTAL;
        this->atk = atk;
        this->atk_range = atk_range;
        this->vis_range = vis_range;
        this->speed = speed;
        this->fraction = fraction;
        this->name = name;
        this->exp = exp;
        this->is_spawner = is_spawner;
        this->spawn_type = spawn_type;
    }

    uint Mortal::getExp() const {
        return exp;
    }

    void Mortal::setExp(const uint new_exp) {
        this->exp = new_exp;
    }

    bool Mortal::isAlive() const {
        return cur_hp > 0;
    }

    EntityType Mortal::getType() const {
        return MORTAL;
    }

}