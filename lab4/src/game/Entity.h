/**
 * @file Entity.h
 * Base class for player and mobs.
 */

#ifndef OOP_ENTITY_H
#define OOP_ENTITY_H

#include <iostream>

#include "enum/Direction.h"
#include "enum/EntityType.h"
#include "enum/Fraction.h"

namespace DungeonGame {

    class Entity {
        /**
         * Base abstract class for player and mobs.
         * Introduces very basic params for all entities.
         */
    protected:
        std::pair<uint, uint> pos; /**< position on level, algebraic coordinate system */
        Direction facing; /**< side where the entity is looking */
        uint max_hp; /**< max HP */
        uint cur_hp; /**< current HP */
        uint atk; /**< damage dealt by entity's normal attack */
        Fraction fraction; /**< which fraction entity belongs to */
        EntityType type;

    public:
        [[nodiscard]] std::pair<uint, uint> getPos() const;

        void setPos(std::pair<uint, uint> pos);
        void setPos(uint x, uint y);

        [[nodiscard]] Direction getFacing() const;

        void setFacing(Direction dir);
        void setFacing(char dir);

        [[nodiscard]] uint getAtk() const;
        void setAtk(uint atk);

        [[nodiscard]] uint getHp() const;
        void setHp(uint hp);

        [[nodiscard]] uint getMaxHp() const;
        void setMaxHp(uint hp);

        [[nodiscard]] Fraction getFraction() const;
        void setFraction(Fraction fraction);

        virtual void damage(uint dmg);

        /**
         * virtual method to 'know what class is it' - useful when working with abstract Entity pointers
         *
         * @return Entity Type of current entity
         */
        [[nodiscard]] virtual EntityType getType() const;
    };
}

#endif //OOP_ENTITY_H
