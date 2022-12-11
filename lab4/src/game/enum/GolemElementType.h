/**
 * @file GolemElementType.h
 * Elemental types of Golems defining their death effect
 *
 * Stone: creates a wall (breakable)
 * Fire: creates a block of lava
 * Ether: transforms into essence
 * Explosive: causes an explosion, dealing AoE damage to all mobs within range and destroying walls nearby
 */

#ifndef OOP_GOLEMELEMENTTYPE_H
#define OOP_GOLEMELEMENTTYPE_H

namespace DungeonGame {

    enum GolemElementType {
        STONE,
        FIRE,
        ETHER,
        EXPLOSIVE
    };

}

#endif //OOP_GOLEMELEMENTTYPE_H
