/**
 * @file Cell.h
 * Types of cells on a map layout
 */

#ifndef OOP_CELL_H
#define OOP_CELL_H


namespace DungeonGame {

    enum Cell {
        FLOOR,
        LAVA,
        WALL,
        BEDROCK,
        ESSENCE,
        DOOR_OPEN,
        DOOR_CLOSED,
        LADDER_UP,
        LADDER_DOWN
    };

}


#endif //OOP_CELL_H
