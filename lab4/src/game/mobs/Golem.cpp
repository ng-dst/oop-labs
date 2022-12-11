#include "Golem.h"
#include "random_num.h"

namespace DungeonGame {

    static Random::RNG gen;

    Golem::Golem(std::pair<uint, uint> pos, uint max_hp, uint atk, uint atk_range,
                 uint vis_range, uint speed, Fraction fraction, const std::string& name,
                 GolemElementType type, float dodge_prob) {
        this->pos = pos;
        this->max_hp = max_hp;
        this->cur_hp = max_hp;
        this->facing = LEFT;
        this->type = GOLEM;
        this->atk = atk;
        this->atk_range = atk_range;
        this->vis_range = vis_range;
        this->speed = speed;
        this->fraction = fraction;
        this->name = name;
        this->golem_type = type;
        this->dodge_prob = dodge_prob;
        this->is_spawner = false;
        this->spawn_type = ZOMBIE;
    }

    GolemElementType Golem::getGolemType() const {
        return golem_type;
    }

    void Golem::setGolemType(const GolemElementType elem_type) {
        golem_type = elem_type;
    }

    float Golem::getDodgeProb() const {
        return this->dodge_prob;
    }

    void Golem::setDodgeProb(const float prob) {
        if (prob < 0. || prob > 1.)
            throw std::invalid_argument("Golem setter:  invalid dodge prob");
        dodge_prob = prob;
    }

    void Golem::damage(const uint dmg) {
        float r = gen.getRandomFloat();
        // '>' = opposite event: no dodge
        if (r > dodge_prob)
            cur_hp = std::max(0, (int) cur_hp - (int) dmg);
    }

    EntityType Golem::getType() const {
        return GOLEM;
    }

}