#include "Level.h"

#include "SimpleIni.h"

#include <iostream>
#include <sstream>
#include <fstream>

namespace DungeonGame {

    UndeadType _undTypeFromStr(const string& s) {
        if      (s == "ZOMBIE")   return UndeadType::ZOMBIE;
        else if (s == "SKELETON") return UndeadType::SKELETON;
        else if (s == "VAMPIRE")  return UndeadType::VAMPIRE;
        else if (s == "GHOUL")    return UndeadType::GHOUL;
        throw invalid_argument("Unknown undead type");
    }

    Fraction _fracFromStr(const string& s) {
        if      (s == "ALLIANCE") return Fraction::ALLIANCE;
        else if (s == "BANDITS")  return Fraction::BANDITS;
        else if (s == "GOBLINS")  return Fraction::GOBLINS;
        else if (s == "ABYSS")    return Fraction::ABYSS;
        else throw invalid_argument("Cannot create mob: unknown fraction type");
    }

    GolemElementType _golemTypeFromStr(const string& s) {
        if      (s == "FIRE")   return GolemElementType::FIRE;
        else if (s == "STONE")  return GolemElementType::STONE;
        else if (s == "ETHER")  return GolemElementType::ETHER;
        else if (s == "EXPLOSIVE")    return GolemElementType::EXPLOSIVE;
        else throw invalid_argument("Cannot create mob: unknown fraction type");
    }


    Level::Level(const string &dir, const uint number, Player& player) {
        if (dir.length() > 250)
            throw std::length_error("Directory name is too long (> 250 chars)");
        ostringstream filename;
        filename << dir << "/level" << number << ".ini";

        // open file
        CSimpleIniA ini;
        SI_Error rc = ini.LoadFile(filename.str().c_str());
        if (rc < 0)
            throw runtime_error("Could not open level config file");

        // Title and initial info
        level_number = number;
        level_title = string(ini.GetValue("Title", "LevelTitle"));
        uint mobs_count = (uint) ini.GetLongValue("Mobs", "MobsCount");
        move_prob = (float) ini.GetDoubleValue("Mobs", "MoveProb");

        // Mobs

        mobs = list<Mob*>();

        for (uint i = 0; i < mobs_count; i++) {
            ostringstream str_section;
            str_section << "Mob" << i;
            const string& str_sect = str_section.str();
            const char* section = str_sect.c_str();

            string name(ini.GetValue(section, "Name"));
            string s_frac(ini.GetValue(section, "Fraction"));
            auto x = (uint) ini.GetLongValue(section, "PosX");
            auto y = (uint) ini.GetLongValue(section, "PosY");
            auto max_hp = (uint) ini.GetLongValue(section, "MaxHp");
            auto atk = (uint) ini.GetLongValue(section, "Atk");
            auto vis_range = (uint) ini.GetLongValue(section, "VisRange");
            auto atk_range = (uint) ini.GetLongValue(section, "AtkRange");
            auto speed = (uint) ini.GetLongValue(section, "Speed");
            UndeadType spawn_type;
            bool is_spawner;

            Fraction frac = _fracFromStr(s_frac);

            string s_type(ini.GetValue(section, "Type"));

            if (s_type == "MORTAL" || s_type == "UNDEAD") {
                is_spawner = ini.GetBoolValue(section, "IsSpawner");
                if (is_spawner) {
                    string s_spawn_type(ini.GetValue(section, "SpawnType"));
                    spawn_type = _undTypeFromStr(s_spawn_type);
                }
            }

            if (s_type == "MORTAL") {
                auto exp = (uint) ini.GetLongValue(section, "Exp");
                auto mob = new Mortal(make_pair(x,y), max_hp, atk, atk_range, vis_range, speed, frac, name, exp, is_spawner, spawn_type);
                mobs.push_back(mob);
            }
            else if (s_type == "UNDEAD") {
                string s_und_type(ini.GetValue(section, "UndeadType"));
                UndeadType und_type = _undTypeFromStr(s_und_type);
                auto mob = new Undead(make_pair(x,y), max_hp, atk, atk_range, vis_range, speed, frac, name, und_type, is_spawner, spawn_type);
                mobs.push_back(mob);
            }
            else if (s_type == "GOLEM") {
                string s_g_type(ini.GetValue(section, "GolemType"));
                GolemElementType g_type = _golemTypeFromStr(s_g_type);
                auto dodge_prob = (float) ini.GetDoubleValue(section, "DodgeProb");
                auto mob = new Golem(make_pair(x,y), max_hp, atk, atk_range, vis_range, speed, frac, name, g_type, dodge_prob);
                mobs.push_back(mob);
            }
        } // end for

        // Map Props
        auto h = (uint) ini.GetLongValue("MapProps", "Height");
        auto w = (uint) ini.GetLongValue("MapProps", "Width");
        level_size = make_pair(h, w);

        auto sp_x = (uint) ini.GetLongValue("MapProps", "SpawnPointX");
        auto sp_y = (uint) ini.GetLongValue("MapProps", "SpawnPointY");

        lava_dmg = (uint) ini.GetDoubleValue("MapProps", "LavaDmg");

        ((Entity&) player).setPos(sp_x, sp_y);

        // Map
        ostringstream str_mapname;
        str_mapname << dir << "/level" << number << "_map.txt";

        Level::loadLevelMap(level_map, h, w, str_mapname.str());

        // return *new Level(number, title, player, *mobs, lava_dmg, move_prob, make_pair(h,w), *field);
    }

    Level::~Level() {
        for (auto mob: mobs)
            delete mob;
    }

    uint Level::getLevelNumber() const { return level_number; }
    const string& Level::getLevelTitle() const { return level_title; }

    pair<uint, uint> Level::getMapSize() const { return level_size; }
    vector<vector<Cell>>& Level::getMap() { return level_map; }

    uint Level::getLavaDmg() const { return lava_dmg; }
    float Level::getMoveProb() const { return move_prob; }

    list<Mob*>& Level::getMobList() { return mobs; }
    Mob* Level::getMob(const pair<uint, uint>& coords) {
        for (Mob* i: mobs)
            if (i->getPos() == coords)
                return i;
        return nullptr;
    }
    Mob* Level::getMob(uint x, uint y) { return getMob(make_pair(x, y)); }

    bool Level::spawnMob(Mob &mob) {
        auto pos = mob.getPos();
        Cell c = level_map.at(pos.first).at(pos.second);
        if (c == Cell::FLOOR ||
            c == Cell::DOOR_OPEN ||
            c == Cell::ESSENCE) {
            for (const auto& i: mobs)
                if (i->getPos() == pos)
                    return false;
            mobs.push_back(&mob);
            return true;
        }
        return false;
    }

    bool Level::rmMob(const std::pair<uint, uint> &pos) {
        for (auto i = mobs.begin(); i != mobs.end(); i++)
            if ((*i)->getPos() == pos) {
                delete *i;
                mobs.erase(i);
                return true;
            }
        return false;
    }

    void Level::loadLevelMap(vector<vector<Cell>> &lvl_map, uint h, uint w, const string &filename) {
        ifstream in(filename);
        if (!in.is_open())
            throw runtime_error("Could not open map file");

        lvl_map.reserve(h);

        string line;
        uint i = 0, j;
        char c;
        Cell cell;
        while (getline(in, line) && i < h) {
            lvl_map.emplace_back();
            lvl_map[i].reserve(w);
            for (j = 0; j < line.length() && j < w; j++) {
                c = line[j];
                switch (c) {
                    case '#': cell = Cell::WALL;        break;
                    case '$': cell = Cell::BEDROCK;     break;
                    case '@': cell = Cell::ESSENCE;     break;
                    case '<': cell = Cell::LADDER_UP;   break;
                    case '>': cell = Cell::LADDER_DOWN; break;
                    case '+': cell = Cell::DOOR_CLOSED; break;
                    case '/': cell = Cell::DOOR_OPEN;   break;
                    case '~': cell = Cell::LAVA;        break;
                    default:  cell = Cell::FLOOR;       break;
                }
                lvl_map[i].push_back(cell);
            }
            i++;
        }
    }

}