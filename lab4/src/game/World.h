/**
 * @file World.h
 * Main game manager class with API for interaction with game process.
 */

#ifndef OOP_WORLD_H
#define OOP_WORLD_H

#include <iostream>
#include <utility>

#include "Level.h"
#include "TalentConfig.h"

using namespace std;

namespace DungeonGame {

    /**
     * Main game manager class. Provides API for interaction with game process,
     * level loading, progress data saving, etc.
     *
     * World is loaded from config file:         world_dir/config.ini
     * Levels are loaded from:            world_dir/levelX.ini ,  world_dir/levelX_map.txt    (X counts from 0)
     * Progress data is saved to / loaded from:  world_dir/saveN.ini    (N counts from 0)
     */
    class World {
        bool game_running;
        string level_dir;
        string save_path;
        uint level_count;
        Level& current_level;
        Player& player_ent;

    public:
        ~World();
        /**
         * load World from its directory, and try to load progress data, if present
         *
         * @param dir - world directory with config.ini, levelX.ini, levelX_map.txt
         * @param save_number - number of save slot, resulting in file  saveN.ini
         * @return reference to World loaded
         *
         * @throw std::length_error - if dir name is too long (> 250)
         * @throw std::runtime_error - if SimpleIni cannot load level config
         */
        static World& fromDir(const string& dir, uint save_number=0);

        World(string  level_dir,
              string  save_path,
              uint level_count,
              Level& first_lvl,
              Player& player):
              level_dir(std::move(level_dir)), save_path(std::move(save_path)),
              level_count(level_count), current_level(first_lvl), player_ent(player), game_running(true) {};

        /**
         * try to load / save player data from current save path
         *
         * @return EXIT_SUCCESS or EXIT_FAILURE
         */
        int loadPlayerData();
        int savePlayerData();

        [[nodiscard]] const string& getLevelDir() const;
        void setLevelDir(const string& dir);

        [[nodiscard]] const string& getSavePath() const;
        void setSavePath(const string& save_path);

        [[nodiscard]] uint getLevelCount() const;
        void setLevelCount(uint level_count);

        Player& getPlayerEnt();

        /**
         * load level by number from world directory, place to current_level
         *
         * @param level_number - number of level to load, counting from 0
         *
         * @throw std::runtime_error, if SimpleIni cannot load level
         */
        void loadLevel(uint level_number);

        Level& getCurrentLevel();

        /**
         * process pressed key from keyboard to make respective move
         *
         * @param key
         * @return true / false, whether player has actually moved (i.e. spent his turn)
         */
        bool movePlayer(char key);

        /**
         * move specified AI-controlled mob
         *
         * @param moving_mob
         */
        void moveOneMob(Mob& moving_mob);

        /**
         * move all AI-controlled mobs on the level
         *
         * Mobs move consequently by fractions. Player's allies move first.
         */
        void moveMobs();

        /**
         * process all dead bodies on the level:
         * give player hp / mana, trigger golems' death effects, etc.
         */
        void processDead();

        /**
         * process all active mobs-spawners on the level,
         * and for each of them try to spawn a new mob
         */
        void doSpawnCycle();

        [[nodiscard]] bool isGameRunning() const;
    };

}
#endif //OOP_WORLD_H
