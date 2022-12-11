/**
 * @file Controls.h
 * Controls map for keyboard keys
 */

#ifndef OOP_KEYS_H
#define OOP_KEYS_H

#include "enum/UndeadType.h"
#include <map>

namespace DungeonGame::Controls {

    const char MoveUp = 'w';
    const char MoveLeft = 'a';
    const char MoveDown = 's';
    const char MoveRight = 'd';

    const char ApplyCurse = 'e';
    const char ApplyUltimate = 'q';

    const char TurnToZombie = 'z';
    const char TurnToSkeleton = 'x';
    const char TurnToVampire = 'c';
    const char TurnToGhoul = 'v';

    const std::map<char, UndeadType> undeadKeys {
            {TurnToZombie, ZOMBIE},
            {TurnToSkeleton, SKELETON},
            {TurnToVampire, VAMPIRE},
            {TurnToGhoul, GHOUL},
    };

    const char AllMoveKeys[] = "wdsa";
}

#endif //OOP_KEYS_H
