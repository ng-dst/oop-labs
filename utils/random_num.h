#ifndef OOP_RANDOM_NUM_H
#define OOP_RANDOM_NUM_H

#include <random>

namespace Random {

    class RNG {
        std::default_random_engine engine;
        std::uniform_real_distribution<> dis_r;
        std::uniform_int_distribution<> dis_i;
    public:
        RNG() {
            std::random_device rd;
            engine = std::default_random_engine(rd());
            dis_r = std::uniform_real_distribution<>(0.0, 1.0);
            dis_i = std::uniform_int_distribution<>(0, INT32_MAX);
        }

        float getRandomFloat() {
            return dis_r(engine);
        }

        int getRandomInt(int a, int b) {
            if (b < a) std::swap(a, b);
            return a + dis_i(engine) % (b - a + 1);
        }
    };

}

#endif //OOP_RANDOM_NUM_H
