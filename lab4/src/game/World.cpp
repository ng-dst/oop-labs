#include "World.h"

#include "Controls.h"
#include "Level.h"
#include "Player.h"
#include "TalentConfig.h"
#include "random_num.h"

#include "SimpleIni.h"

#include <iostream>
#include <sstream>

using namespace std;

namespace DungeonGame {

    static Random::RNG gen;

    static pair<int, int> _getDeltaByKey(char key) {
        int dx=0, dy=0;
        switch (key) {
            case Controls::MoveUp:
                dx = -1; break;
            case Controls::MoveLeft:
                dy = -1; break;
            case Controls::MoveDown:
                dx =  1; break;
            case Controls::MoveRight:
                dy =  1; break;
            default:
                dx = 0;
                dy = 0;
        }
        return make_pair(dx, dy);
    }

    World& World::fromDir(const string &dir, uint save_number) {
        if (dir.length() > 250)
            throw std::length_error("Directory name is too long (> 250 chars)");

        string filename = dir + "/config.ini";
        const char* c_filename = filename.c_str();

        // open file
        CSimpleIniA ini;
        SI_Error rc = ini.LoadFile(c_filename);
        if (rc < 0)
            throw runtime_error("Could not open level config file");

        // Levels
        uint level_count = ini.GetLongValue("Levels", "LevelsCount");

        // Player
        uint p_max_hp = ini.GetLongValue("Player", "PlayerMaxHpBase");
        uint p_max_mana = ini.GetLongValue("Player", "PlayerMaxManaBase");
        uint p_atk = ini.GetLongValue("Player", "PlayerAtkBase");

        // TalentConfig
        TalentConfig& tc = loadTalentConfig(ini);
        map<Talent, uint>& talents = *new map<Talent, uint>();
        talents[Talent::CURSE] = 1;
        talents[Talent::WITHERING] = 1;
        talents[Talent::NECROMANCY] = 1;
        talents[Talent::MORPHISM] = 1;
        talents[Talent::ULTIMATE] = 1;

        Player& p = *new Player(make_pair(0,0), p_max_hp, p_atk, Fraction::ALLIANCE, p_max_mana, 0, 1, talents, 0, tc);
        Level& lvl = *new Level(dir, 0, p);

        ostringstream save_path;
        save_path << "/save" << save_number << ".ini";

        auto w = new World(dir, dir + save_path.str(), level_count, lvl, p);

        // try to load player data, if present
        w->loadPlayerData();

        return *w;
    }

    World::~World() {
        delete &current_level;
        delete &player_ent;
    }

    int World::loadPlayerData() {
        CSimpleIniA ini;
        SI_Error rc = ini.LoadFile(save_path.c_str());
        if (rc < 0) return EXIT_FAILURE;

        uint cur_level = ini.GetLongValue("Level", "CurrentLevel");
        if (cur_level != current_level.getLevelNumber())
            loadLevel(cur_level);

        player_ent.setHp(ini.GetLongValue("Player", "CurrentHp", player_ent.getMaxHp()));
        player_ent.setLevel(ini.GetLongValue("Player", "PlayerLevel", 1));
        player_ent.setExp(ini.GetLongValue("Player", "PlayerExp"));
        player_ent.setTalentPoints(ini.GetLongValue("Player", "TalentPoints"));

        player_ent.setTalentLevel(Talent::WITHERING, ini.GetLongValue("Talents", "WITHERING", 1));
        player_ent.setTalentLevel(Talent::CURSE, ini.GetLongValue("Talents", "CURSE", 1));
        player_ent.setTalentLevel(Talent::NECROMANCY, ini.GetLongValue("Talents", "NECROMANCY", 1));
        player_ent.setTalentLevel(Talent::MORPHISM, ini.GetLongValue("Talents", "MORPHISM", 1));
        player_ent.setTalentLevel(Talent::ULTIMATE, ini.GetLongValue("Talents", "ULTIMATE", 1));

        return EXIT_SUCCESS;
    }

    int World::savePlayerData() {
        CSimpleIniA ini;

        ini.SetLongValue("Level", "CurrentLevel", current_level.getLevelNumber());
        ini.SetLongValue("Player", "PlayerLevel", player_ent.getLevel());
        ini.SetLongValue("Player", "PlayerExp", player_ent.getExp());
        ini.SetLongValue("Player", "TalentPoints", player_ent.getTalentPoints());

        ini.SetLongValue("Talents", "WITHERING", player_ent.getTalentLevel(Talent::WITHERING));
        ini.SetLongValue("Talents", "CURSE", player_ent.getTalentLevel(Talent::CURSE));
        ini.SetLongValue("Talents", "NECROMANCY", player_ent.getTalentLevel(Talent::NECROMANCY));
        ini.SetLongValue("Talents", "MORPHISM", player_ent.getTalentLevel(Talent::MORPHISM));
        ini.SetLongValue("Talents", "ULTIMATE", player_ent.getTalentLevel(Talent::ULTIMATE));

        SI_Error rc = ini.SaveFile(save_path.c_str());
        if (rc < 0) return EXIT_FAILURE;

        return EXIT_SUCCESS;
    }

    const string& World::getLevelDir() const { return level_dir; }
    void World::setLevelDir(const string& dir) { level_dir = dir;}

    const string& World::getSavePath() const { return save_path; }
    void World::setSavePath(const string& path) { save_path = path; }

    uint World::getLevelCount() const { return level_count; }
    void World::setLevelCount(uint count) { level_count = count; }

    Player& World::getPlayerEnt() { return player_ent; }
    void World::loadLevel(uint level_number) {
        for (auto mob: current_level.getMobList())
            delete mob;
        current_level = *new Level(level_dir, level_number, player_ent);
        game_running = true;
    }
    Level& World::getCurrentLevel() { return current_level; }

    bool World::isGameRunning() const { return game_running; }

    bool World::movePlayer(char key) {
        pair<uint, uint> size = current_level.getMapSize();
        pair<int, int> delta_move = _getDeltaByKey(key);
        int dx = delta_move.first, dy = delta_move.second;

        if (current_level.getMap()[player_ent.getPos().first][player_ent.getPos().second] == Cell::LAVA)
            player_ent.damage(current_level.getLavaDmg());

        bool all_enemies_dead = true;
        if (dx != 0 || dy != 0) {
            if (key != Controls::AllMoveKeys[player_ent.getFacing()]) {
                player_ent.setFacing(key);
                return false;
            }
            player_ent.setFacing(key);
            pair<int, int> new_pos = player_ent.getPos();
            new_pos.first += dx;
            new_pos.second += dy;
            if (new_pos.first  < 0 || new_pos.first  >= size.first ||
                new_pos.second < 0 || new_pos.second >= size.second)
                return false;

            if (auto mob = current_level.getMob(new_pos)) {
                // trying to move through the mob
                if (mob->getFraction() == Fraction::ALLIANCE ||
                    mob->getType() == EntityType::MORTAL && mob->getHp() == 0) {
                    // swap positions with ally or dead
                    mob->setPos(player_ent.getPos());
                    player_ent.setPos(new_pos);
                } else {
                    // normal attack
                    mob->damage(player_ent.getAtk());
                }
                return true;
            }

            switch (current_level.getMap()[new_pos.first][new_pos.second]) {
                case Cell::WALL:
                case Cell::BEDROCK:
                case Cell::LADDER_UP:
                    return false;

                case Cell::DOOR_CLOSED:
                    current_level.getMap()[new_pos.first][new_pos.second] = Cell::DOOR_OPEN;
                    break;

                case Cell::LADDER_DOWN:
                    for (auto i: current_level.getMobList())
                        if (i->getFraction() != Fraction::ALLIANCE && i->getHp() > 0) {
                            all_enemies_dead = false;
                        }
                    if (all_enemies_dead) {
                        if (current_level.getLevelNumber() == level_count - 1) {
                            game_running = false;
                        }
                    } else return false;
                    break;

                case Cell::ESSENCE:
                    player_ent.setTalentPoints(player_ent.getTalentPoints() + 1);
                    player_ent.setMana(min(player_ent.getMaxMana(),
                                           player_ent.getMana() + 2 * (player_ent.getTalentConfig().WitheringManaBase +
                                           (player_ent.getTalentLevel(WITHERING) *
                                           player_ent.getTalentConfig().WitheringManaAffix))));
                    current_level.getMap()[new_pos.first][new_pos.second] = Cell::FLOOR;
                default:;
            }
            player_ent.setPos(new_pos);
            return true;
        }

        Mob* mob = nullptr;
        pair<int, int> delta_facing = _getDeltaByKey(Controls::AllMoveKeys[player_ent.getFacing()]);
        pair<uint, uint> facing_pos = player_ent.getPos();
        facing_pos.first += delta_facing.first;
        facing_pos.second += delta_facing.second;

        if (key == Controls::ApplyCurse)
            return player_ent.applyCurse(current_level);
        if (key == Controls::ApplyUltimate)
            return player_ent.applyUltimate(current_level);

        if (Controls::undeadKeys.find(key) != Controls::undeadKeys.end() && current_level.getMob(facing_pos)) {
            if (current_level.getMob(facing_pos)->getType() == MORTAL) {
                mob = player_ent.applyNecromancy(*current_level.getMob(facing_pos), Controls::undeadKeys.at(key));
                if (mob) {
                    current_level.rmMob(facing_pos);
                    current_level.spawnMob(*mob);
                    return true;
                }
            }
            if (current_level.getMob(facing_pos)->getType() == UNDEAD) {
                mob = player_ent.applyMorphism(*current_level.getMob(facing_pos), Controls::undeadKeys.at(key));
                if (mob) return true;
            }
        }

        return false;
    }

    void World::moveMobs() {
        for (const auto frac: {Fraction::ALLIANCE, Fraction::BANDITS, Fraction::GOBLINS, Fraction::ABYSS})
            for (auto moving_mob: current_level.getMobList()) {
                if (moving_mob->getFraction() == frac && moving_mob->getHp() > 0) {
                    moveOneMob(*moving_mob);
                    if (current_level.getMap()[moving_mob->getPos().first][moving_mob->getPos().second] == Cell::LAVA)
                        moving_mob->damage(current_level.getLavaDmg());
                }
            }
    }

    void World::moveOneMob(Mob &moving_mob) {
        RangeCalc calc(current_level.getMap());
        uint range;
        // search for enemy
        list<Entity*> enemy_list;
        for (auto i: current_level.getMobList())
            enemy_list.push_back(i);
        enemy_list.push_back((Entity*) &player_ent);

        for (auto enemy: enemy_list) {
            if (enemy->getFraction() != moving_mob.getFraction() &&
                (range = calc.range(moving_mob.getPos(), enemy->getPos())) > 0 && range <= moving_mob.getVisRange()) {
                // found enemy
                if (range < moving_mob.getAtkRange())
                    // if in attack range => attack
                    enemy->damage(moving_mob.getAtk());
                else {
                    // not in attack range => move towards enemy
                    pair<uint, uint> cur_pos = moving_mob.getPos();
                    uint remaining_moves = min(moving_mob.getSpeed(), range-1);
                    auto path = calc.path(moving_mob.getPos(), enemy->getPos(),
                                          moving_mob.getAtkRange(), moving_mob.getVisRange());
                    auto it = path.begin();
                    while (it != path.end() && remaining_moves-- != 0)
                        if (gen.getRandomFloat() < current_level.getMoveProb()) {
                            moving_mob.setFacing(*it);
                            auto delta = _getDeltaByKey(
                                    Controls::AllMoveKeys[
                                            *(it++)]
                                            );
                            cur_pos.first += delta.first;
                            cur_pos.second += delta.second;
                            if (current_level.getMap()[cur_pos.first][cur_pos.second] == Cell::LAVA)
                                moving_mob.damage(current_level.getLavaDmg());
                        }
                    if (current_level.getMob(cur_pos) == nullptr && player_ent.getPos() != cur_pos)
                        moving_mob.setPos(cur_pos);
                }
            break;
            }
        }
    }

    void World::processDead() {
        list<pair<uint, uint>> to_rm;
        for (auto mob: current_level.getMobList())
            if (mob->getHp() == 0) {
                if (mob->getType() == EntityType::MORTAL) {
                    player_ent.incExp(((Mortal*) mob)->getExp());
                    ((Mortal*) mob)->setExp(0);
                }
                else {
                    // remove dead mobs that are not mortals,  refill hp & mana (withering)

                    uint withering_lvl = player_ent.getTalentLevel(Talent::WITHERING);
                    uint dhp = mob->getMaxHp() * (player_ent.getTalentConfig().WitheringHpBase +
                                                  withering_lvl * player_ent.getTalentConfig().WitheringHpAffix);
                    uint dmana = player_ent.getTalentConfig().WitheringManaBase +
                                 withering_lvl * player_ent.getTalentConfig().WitheringManaAffix;
                    player_ent.setMana(min(player_ent.getMana() + dmana, player_ent.getMaxMana()));
                    player_ent.setHp(min(player_ent.getHp() + dhp, player_ent.getMaxHp()));

                    // process golems
                    int x = mob->getPos().first, y = mob->getPos().second;
                    if (mob->getType() == EntityType::GOLEM)
                        switch (((Golem *) mob)->getGolemType()) {
                            case STONE:
                                current_level.getMap()[x][y] = Cell::WALL;
                                break;
                            case FIRE:
                                current_level.getMap()[x][y] = Cell::LAVA;
                                break;
                            case ETHER:
                                current_level.getMap()[x][y] = Cell::ESSENCE;
                                break;
                            case EXPLOSIVE:
                                auto &field = current_level.getMap();
                                int atk_range = mob->getAtkRange();
                                for (int i = max(0, x - atk_range); i < min((int) field.size(), x + atk_range + 1); i++)
                                    for (int j = max(0, y - atk_range + x - i + 1);
                                         j < min((int) field[0].size(), y + atk_range - x + i); j++)
                                        if (field[i][j] == Cell::DOOR_CLOSED ||
                                            field[i][j] == Cell::DOOR_OPEN ||
                                            field[i][j] == Cell::WALL)
                                            field[i][j] = Cell::FLOOR;
                                auto calc = RangeCalc(current_level.getMap());
                                uint range;
                                list<Entity *> enemy_list;
                                for (auto i: current_level.getMobList())
                                    enemy_list.push_back(i);
                                enemy_list.push_back((Entity *) &player_ent);
                                for (auto target: enemy_list) {
                                    if ((range = calc.range(make_pair(x, y), target->getPos())) > 0 &&
                                        range < atk_range + 1)
                                        target->damage((current_level.getLavaDmg() + mob->getAtk()) * 3 / (1 + range));
                                }
                                break;
                        }
                    to_rm.push_back(mob->getPos());
                    if (mob->getFraction() == player_ent.getFraction() &&
                        mob->getType() == UNDEAD && player_ent.getServantCount() != 0)
                        player_ent.setServantCount(player_ent.getServantCount() - 1);
                }
            }

        for (auto i: to_rm)
            current_level.rmMob(i);

        if (player_ent.getHp() <= 0) {
            game_running = false;
            return;
        }
    }

    void World::doSpawnCycle() {
        uint h = current_level.getMapSize().first, w = current_level.getMapSize().second;
        for (auto mob: current_level.getMobList())
            if (mob->getHp() > 0 && mob->isSpawner()) {
                pair<int, int> pos = mob->getPos();
                int x, y;
                int range = mob->getAtkRange();
                if (gen.getRandomFloat() < current_level.getMoveProb() * .20f) {
                    x = pos.first + gen.getRandomInt(-range, range);
                    y = pos.second + gen.getRandomInt(-range, range);
                    if (x >= 0 && x < h && y >= 0 && y < w && current_level.getMap()[x][y] == FLOOR &&
                             current_level.getMob(make_pair(x,y)) == nullptr && player_ent.getPos() != make_pair((uint) x, (uint) y)) {
                        Undead& und = *new Undead(make_pair(x,y),
                                                      mob->getMaxHp()/8,
                                                      mob->getAtk()/4,
                                                      mob->getAtkRange(),
                                                      mob->getVisRange(),
                                                      mob->getSpeed(),
                                                      mob->getFraction(),
                                                      "Servant of " + mob->getName(),
                                                      mob->getSpawnType());
                        current_level.spawnMob(und);
                    }
                }
            }
    }
}
