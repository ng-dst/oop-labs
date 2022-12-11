#include "../../Google_tests/lib/googletest/include/gtest/gtest.h"

#include "mobs/Golem.h"
#include "mobs/Mortal.h"
#include "mobs/Undead.h"

using namespace std;

TEST (UndeadTest, UndeadFromBody) {
    DungeonGame::Mortal body = DungeonGame::Mortal(make_pair(0,0), 100, 40,
                                                   3, 6, 1, DungeonGame::BANDITS,
                                                   "test subject", 35, true, DungeonGame::ZOMBIE);
    body.damage(1000);
    ASSERT_FALSE(body.isAlive());
    DungeonGame::Undead undead = DungeonGame::Undead(body, DungeonGame::GHOUL);

    ASSERT_EQ(body.getMaxHp(), undead.getMaxHp());
    ASSERT_EQ(body.isSpawner(), undead.isSpawner());
}


TEST (GeneralMobTest, TakeDamage) {
    DungeonGame::Mortal mob = DungeonGame::Mortal(make_pair(0,0), 100, 40,
                                                  3, 6, 1, DungeonGame::BANDITS,
                                                  "test subject", 35, true, DungeonGame::ZOMBIE);
    mob.damage(20);
    ASSERT_EQ(100-20, mob.getHp());
    mob.damage(100);
    ASSERT_EQ(0, mob.getHp());
    ASSERT_FALSE(mob.isAlive());
}

