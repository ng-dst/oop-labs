#include "Player.h"
#include "enum/Talent.h"
#include "mobs/Undead.h"

namespace DungeonGame {

    Player::Player(pair<uint, uint> pos, uint max_hp, uint atk, Fraction fraction,
                   uint max_mana, uint exp, uint level, map<Talent, uint>& talents,
                   uint talent_points, TalentConfig& talent_config): talents(talents), talent_config(talent_config) {
        this->pos = pos;
        this->facing = RIGHT;
        this->cur_hp = max_hp;
        this->max_hp = max_hp;
        this->atk = atk;
        this->fraction = fraction;
        this->max_mana = max_mana;
        this->mana = 0u;

        this->level = level;
        this->talent_points = talent_points;
        this->talent_config = talent_config;
        if (talent_config.ExpPerLevel == 0)
            throw std::logic_error("Player(): cannot initialize with zero ExpPerLevel");

        this->servant_count = 0u;

        this->exp = 0u;
        incExp(exp);
    }

    Player::~Player() {
        delete &talents;
        delete &talent_config;
    }

    uint Player::getMana() const { return mana; }
    void Player::setMana(uint new_mana) { this->mana = new_mana; }

    uint Player::getMaxMana() const { return max_mana; }
    void Player::setMaxMana(uint new_mana) { this->max_mana = new_mana; }

    uint Player::getLevel() const { return level; }
    void Player::setLevel(uint lvl) { level = lvl; }
    uint Player::getExp() const { return exp; }
    void Player::setExp(uint xp) { exp = xp;}

    void Player::incExp(uint dexp) {
        this->exp += dexp;
        uint dlevel = exp / talent_config.ExpPerLevel;
        this->exp %= talent_config.ExpPerLevel;

        this->level += dlevel;
        this->talent_points += dlevel;
        this->atk += dlevel * talent_config.PlayerAtkAffix;
        this->max_hp += dlevel * talent_config.PlayerMaxHpAffix;
        this->max_mana += dlevel * talent_config.PlayerMaxManaAffix;
    }

    uint Player::getTalentLevel(Talent talent) const { return talents[talent]; }
    void Player::setTalentLevel(Talent talent, uint tlevel) { talents[talent] = tlevel; }

    uint Player::getTalentPoints() const { return talent_points; }
    void Player::setTalentPoints(uint points) { talent_points = points; }

    uint Player::getServantCount() const { return servant_count; }
    void Player::setServantCount(uint count) { servant_count = count; }

    const TalentConfig& Player::getTalentConfig() const { return talent_config; }

    Mob* Player::applyNecromancy(Mob& victim, UndeadType type) {
        // checks mob type and if it's dead
        if (victim.getType() != EntityType::MORTAL || ((Mortal*) &victim)->isAlive()) return nullptr;

        // checks if player has enough talent level for this type
        uint talent_lvl = talents.at(Talent::NECROMANCY);
        if (talent_lvl < talent_config.NecromancyRequiredLevels.at(type)) return nullptr;

        // checks if player has enough mana, and not exceeded max servants limit
        uint cost = talent_config.NecromancyCostBase + talent_lvl*talent_config.NecromancyCostAffix;
        uint max_serv = talent_config.NecromancyMaxServantsBase + talent_lvl*talent_config.NecromancyMaxServantsAffix;
        if (mana < cost || servant_count >= max_serv) return nullptr;

        // checks passed, creating new mob based on the victim
        auto mob = new Undead(*((Mortal*) &victim), type);
        mob->setHp(mob->getMaxHp() / 2 + 1);
        mob->setAtk(mob->getAtk() * talent_config.MorphismAtkMul[type]);
        mob->setAtkRange(mob->getAtkRange() + talent_config.MorphismRanges[type] - 1);
        mob->setVisRange(mob->getVisRange() + talent_config.MorphismRanges[type] - 1);
        mob->setUndeadType(type);
        mob->setFraction(fraction);

        servant_count++;
        mana -= cost;

        return mob;
    }

    Mob* Player::applyMorphism(Mob &victim, UndeadType type) {
        // checks mob type; no fraction check => to allow player to weaken enemies
        if (victim.getType() != UNDEAD) return nullptr;

        // checks if types aren't the same, and if player has enough level for BOTH types
        UndeadType new_type = ((Undead*) &victim)->getUndeadType();
        if (type == new_type ||
            talents.at(NECROMANCY) < talent_config.NecromancyRequiredLevels.at(type) ||
            talents.at(NECROMANCY) < talent_config.NecromancyRequiredLevels.at(new_type))
            return nullptr;

        // checks if player has enough mana
        uint talent_lvl = talents.at(MORPHISM);
        uint cost = talent_config.MorphismCostBase + talent_lvl*talent_config.MorphismCostAffix;
        if (mana < cost) return nullptr;

        // checks passed, transforming mob, adjusting stats
        uint new_atk = (uint) ((float) victim.getAtk() * talent_config.MorphismAtkMul.at(new_type)
                                                       / talent_config.MorphismAtkMul.at(type));
        victim.setAtk(max(new_atk, 1u));

        ((Undead*) &victim)->setUndeadType(type);
        if (victim.getFraction() == fraction) victim.setHp(victim.getMaxHp());

        int new_atk_range = victim.getAtkRange() + talent_config.MorphismRanges.at(new_type)
                                                  - talent_config.MorphismRanges.at(type);
        int new_vis_range = victim.getVisRange() + new_atk_range - victim.getAtkRange();
        victim.setAtkRange(max(new_atk_range, 1));
        victim.setVisRange(max(new_vis_range, 1));

        mana -= cost;

        return &victim;
    }

    bool Player::applyCurse(Level &field) {
        return _aoeDmg(field, CURSE);
    }

    bool Player::applyUltimate(Level& field) {
        return _aoeDmg(field, ULTIMATE);
    }

    EntityType Player::getType() const {
        return PLAYER;
    }


    bool Player::_aoeDmg(Level& field, const Talent type) {
        // talents which deal AoE damage
        if (type != CURSE && type != ULTIMATE) return false;

        // check if player has enough mana
        if (type == CURSE    && mana < talent_config.CurseCost   ) return false;
        if (type == ULTIMATE && mana < talent_config.UltimateCost) return false;

        // calculate damage
        uint talent_lvl = talents.at(type);
        uint dmg = (type == CURSE)
                   ? (uint) ( (talent_config.CurseDmgBase + talent_config.CurseDmgAffix*talent_lvl) * atk )
                   : (uint) ( (talent_config.UltimateDmgBase + talent_config.UltimateDmgAffix*talent_lvl) * atk );

        int range, max_range;
        RangeCalc calc(field.getMap());

        for (auto mob: field.getMobList()) {
            // skip mobs of player's fraction
            if (mob->getFraction() == getFraction())
                continue;

            // check if mob is within range;  Curse is directed, Ultimate is not
            range = (type == CURSE)
                    ? calc.range(pos, mob->getPos(), true, facing)
                    : calc.range(pos, mob->getPos());

            max_range = (type == CURSE)
                        ? talent_config.CurseRange
                        : talent_config.UltimateRange;

            if (range > 0 && range <= max_range)
                mob->damage(dmg);
        }

        mana -= (type == CURSE)
                ? talent_config.CurseCost
                : talent_config.UltimateCost;

        return true;
    }
}