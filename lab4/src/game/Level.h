/**
 * @file Level.h
 * Class for level map containing map layout and list of mobs
 */

#ifndef OOP_LEVEL_H
#define OOP_LEVEL_H

#include <iostream>
#include <vector>
#include <map>

#ifdef USE_TEMPLATE
#include "my_list.h"
#define list_ my_list
#else
#include <list>
#define list_ list
#endif

#include "mobs/Golem.h"
#include "mobs/Mortal.h"
#include "mobs/Undead.h"

#include "TalentConfig.h"
#include "enum/Cell.h"

using namespace std;

namespace DungeonGame {

    class Player;

    /**
     * Level - contains map and list of mobs on the level
     *
     * Each level has its number and title.
     * Numbers start with 0 and increment with each new level.
     * Level is loaded from two files:
     *     -   levelX.ini       -  level config and list of mobs
     *     -   level_mapX.txt   -  level map, denoted by the following symbols
     *
     * '.' - floor
     *
     * '#' - wall, can be broken by explosions
     *
     * '$' - bedrock, cannot be broken
     *
     * '@' - essence, gives player 1 talent point and some mana
     *
     * '~' - lava, deals damage upon stepping
     *
     * '+' - closed door
     *
     * '/' - open door
     *
     * '<' - ladder from above, spawnpoint
     *
     * '>' - ladder down, finish point
     */
    class Level {
        uint level_number; /**< number of current level, 0..N-1 */
        string level_title; /**< title of the level */
        list_<Mob*> mobs; /**< list of pointers to mobs on the current level */
        pair<uint, uint> level_size; /**< (height, width) of map */
        vector<vector<Cell>> level_map; /**< level map, represented as 2D vector */
        uint lava_dmg; /**< damage dealt by lava each turn */
        float move_prob; /**< probability of one mob movement per each of mob.Speed attempts */

    public:
        /**
         * Load level from directory by number
         *
         * @param dir - level directory
         * @param number - level number (0..N-1)
         * @param player - reference to player
         */
        Level(const string& dir, uint number, Player& player);
        ~Level();

        // static Level& fromDir(const string& dir, const uint number, Player& player);
        /**
         * Loads level map from file, writes to lvl_map by reference
         *
         * @param lvl_map - reference to 2D vector of cells
         * @param h - map height
         * @param w - map width
         * @param filename - file to read
         */
        static void loadLevelMap(vector<vector<Cell>>& lvl_map, uint h, uint w, const string& filename);

        [[nodiscard]] uint getLevelNumber() const;
        [[nodiscard]] const string& getLevelTitle() const;

        [[nodiscard]] pair<uint, uint> getMapSize() const;
        vector<vector<Cell>>& getMap();

        [[nodiscard]] float getMoveProb() const;

        list_<Mob*>& getMobList();

        /**
         * get mob by cell coordinates (algebraic system)
         *
         * @param coords
         * @return pointer to mob, if found; nullptr, otherwise
         */
        Mob* getMob(const pair<uint, uint>& coords);
        Mob* getMob(uint x, uint y);

        /**
         * try to place a mob on the level
         *
         * @param mob - reference to mob to spawn
         * @return true / false, whether spawned successfully
         */
        bool spawnMob(Mob& mob);

        /**
         * try to remove a mob on specified cell
         *
         * @param pos - pair of mob coordinates (algebraic)
         * @return true / false, whether removed successfully
         */
        bool rmMob(const std::pair<uint, uint>& pos);

        [[nodiscard]] uint getLavaDmg() const;

    };
}

#endif //OOP_LEVEL_H
