/**
 * @file Talent.h
 * Types of player's talents
 *
 * Withering (passive talent) - regains some HP and Mana upon killing an opponent
 * Curse - deals medium AoE damage in player's sight direction
 * Necromancy - transforms dead body of any Mortal into Undead of choice, making it your servant
 * Morphism - transforms any Undead (ally or enemy) into another type of choice
 * Ultimate - deals massive AoE damage around player
 */

#ifndef OOP_TALENT_H
#define OOP_TALENT_H

namespace DungeonGame {

    enum Talent {
        WITHERING,
        CURSE,
        NECROMANCY,
        MORPHISM,
        ULTIMATE
    };

}

#endif //OOP_TALENT_H
