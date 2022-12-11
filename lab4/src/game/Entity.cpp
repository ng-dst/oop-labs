#include "Entity.h"
#include "Controls.h"

namespace DungeonGame {

    std::pair<uint, uint> Entity::getPos() const { return pos; }
    void Entity::setPos(std::pair<uint, uint> new_pos) { pos = new_pos; }
    void Entity::setPos(uint x, uint y) { pos = std::make_pair(x, y); }

    Direction Entity::getFacing() const { return facing; }
    void Entity::setFacing(Direction dir) { facing = dir; }
    void Entity::setFacing(char dir) {
        switch (dir) {
            case Controls::MoveUp:     facing = Direction::UP;     break;
            case Controls::MoveLeft:   facing = Direction::LEFT;   break;
            case Controls::MoveDown:   facing = Direction::DOWN;   break;
            case Controls::MoveRight:  facing = Direction::RIGHT;  break;
            default:;
        }
    }

    uint Entity::getAtk() const { return atk; }
    void Entity::setAtk(uint new_atk) { atk = new_atk; }

    uint Entity::getHp() const { return cur_hp; }
    void Entity::setHp(uint new_hp) { cur_hp = new_hp; }

    uint Entity::getMaxHp() const { return max_hp; }
    void Entity::setMaxHp(uint new_hp) { max_hp = new_hp; }

    Fraction Entity::getFraction() const { return fraction; }
    void Entity::setFraction(const Fraction new_fraction) { fraction = new_fraction; }

    void Entity::damage(uint dmg) { cur_hp = std::max(0, (int) cur_hp - (int) dmg); }

    EntityType Entity::getType() const { return type; }

}