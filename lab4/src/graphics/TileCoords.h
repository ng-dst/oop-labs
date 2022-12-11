#ifndef OOP_TILECOORDS_H
#define OOP_TILECOORDS_H

#include "Player.h"

static const map<DungeonGame::Cell, pair<int, int>> tile_coords {
        {DungeonGame::FLOOR, make_pair(48, 64)},
        {DungeonGame::WALL, make_pair(32, 16)},
        {DungeonGame::BEDROCK, make_pair(48, 48)},
        {DungeonGame::LAVA, make_pair(64, 16)},
        {DungeonGame::ESSENCE, make_pair(64, 48)},
        {DungeonGame::DOOR_CLOSED, make_pair(80, 96)},
        {DungeonGame::DOOR_OPEN, make_pair(96, 144)},
        {DungeonGame::LADDER_DOWN, make_pair(48, 96)},
        {DungeonGame::LADDER_UP, make_pair(48, 96)}
};

static const map<DungeonGame::Direction, pair<int, int>> player_tile_coords {
        {DungeonGame::RIGHT, make_pair(400, 268)},
        {DungeonGame::LEFT, make_pair(416, 268)},
        {DungeonGame::UP, make_pair(384, 268)},
        {DungeonGame::DOWN, make_pair(368, 268)}
};

static const map<pair<DungeonGame::UndeadType, DungeonGame::Direction>, pair<int, int>> undead_tile_coords {
        {make_pair(DungeonGame::ZOMBIE, DungeonGame::RIGHT), make_pair(368, 144)},
        {make_pair(DungeonGame::ZOMBIE, DungeonGame::LEFT), make_pair(384, 144)},
        {make_pair(DungeonGame::ZOMBIE, DungeonGame::UP), make_pair(384, 144)},
        {make_pair(DungeonGame::ZOMBIE, DungeonGame::DOWN), make_pair(400, 144)},

        {make_pair(DungeonGame::SKELETON, DungeonGame::RIGHT), make_pair(368, 80)},
        {make_pair(DungeonGame::SKELETON, DungeonGame::LEFT), make_pair(384, 80)},
        {make_pair(DungeonGame::SKELETON, DungeonGame::UP), make_pair(384, 80)},
        {make_pair(DungeonGame::SKELETON, DungeonGame::DOWN), make_pair(400, 80)},

        {make_pair(DungeonGame::VAMPIRE, DungeonGame::RIGHT), make_pair(368+64, 144)},
        {make_pair(DungeonGame::VAMPIRE, DungeonGame::LEFT), make_pair(384+64, 144)},
        {make_pair(DungeonGame::VAMPIRE, DungeonGame::UP), make_pair(384+64, 144)},
        {make_pair(DungeonGame::VAMPIRE, DungeonGame::DOWN), make_pair(400+64, 144)},

        {make_pair(DungeonGame::GHOUL, DungeonGame::RIGHT), make_pair(368, 172)},
        {make_pair(DungeonGame::GHOUL, DungeonGame::LEFT), make_pair(384, 172)},
        {make_pair(DungeonGame::GHOUL, DungeonGame::UP), make_pair(384, 172)},
        {make_pair(DungeonGame::GHOUL, DungeonGame::DOWN), make_pair(400, 172)}
};

static const map<DungeonGame::Direction, pair<int, int>> mortal_tile_coords {
        {DungeonGame::RIGHT, make_pair(128, 176)},
        {DungeonGame::LEFT, make_pair(160, 176)},
        {DungeonGame::UP, make_pair(160, 176)},
        {DungeonGame::DOWN, make_pair(192, 176)}
};

static const map<DungeonGame::GolemElementType, pair<int, int>> golem_tile_coords {
        {DungeonGame::STONE, make_pair(368, 112)},
        {DungeonGame::FIRE, make_pair(368, 48)},
        {DungeonGame::ETHER, make_pair(432, 112)},
        {DungeonGame::EXPLOSIVE, make_pair(400, 300)}
};


#endif //OOP_TILECOORDS_H
