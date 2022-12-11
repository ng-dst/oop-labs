#include "../../Google_tests/lib/googletest/include/gtest/gtest.h"

#include "World.h"
#include "Player.h"
#include "Controls.h"

#define PATH "/home/pacan/Desktop/C/labs/oop/lab4/levels/t_corpus"


TEST (ConfigLoadTest, WorldConfig) {
    DungeonGame::World& w = DungeonGame::World::fromDir(PATH, 99);
    DungeonGame::Player& p = w.getPlayerEnt();
    ASSERT_EQ(100, ((DungeonGame::Entity&) p).getMaxHp());
    ASSERT_EQ(100, ((DungeonGame::Entity&) p).getHp());
    ASSERT_EQ(55, ((DungeonGame::Entity&) p).getAtk());
    ASSERT_EQ(30, w.getCurrentLevel().getLavaDmg());

    w.setSavePath("/home/pacan/Desktop/C/labs/oop/lab4/levels/t_corpus/save0.ini");
    ASSERT_EQ(EXIT_SUCCESS, w.loadPlayerData());
    ASSERT_EQ(1, p.getLevel());

    w.setSavePath("/home/pacan/Desktop/C/labs/oop/lab4/levels/t_corpus/save1.ini");
    ASSERT_EQ(EXIT_SUCCESS, w.savePlayerData());
    p.setLevel(2);

    w.loadPlayerData();
    ASSERT_EQ(1, p.getLevel());

    delete &w;
}


TEST (ConfigLoadTest, LevelSwitch) {
    DungeonGame::World& w = DungeonGame::World::fromDir(PATH, 0);
    w.loadLevel(1);
    ASSERT_EQ(45, w.getCurrentLevel().getLavaDmg());

    delete &w;
}


TEST (AiLogicTest, AiCanKillPlayer) {
    DungeonGame::World& w = DungeonGame::World::fromDir(PATH, 0);
    DungeonGame::Player& p = w.getPlayerEnt();

    // teleport player out of spawnpoint, where he can't be attacked
    p.setPos(make_pair(2, 0));

    // check if mobs can find and kill player in 100 moves (almost guaranteed)
    // to do so, they have to approach the player, and then attack him
    for (int i = 0; i < 100 && w.isGameRunning(); i++)
        w.moveMobs();

    w.processDead();

    ASSERT_EQ(0, p.getHp());
    ASSERT_FALSE(w.isGameRunning());

    delete &w;
}


TEST (AiLogicTest, AiCanSummonMobs) {
    DungeonGame::World& w = DungeonGame::World::fromDir(PATH, 0);
    DungeonGame::Player& p = w.getPlayerEnt();

    // mobs won't see player, so they won't move, though spawners will still be working
    for (int i = 0; i < 6; i++) {
        w.moveMobs();
        w.doSpawnCycle();
    }

    auto& moblist = w.getCurrentLevel().getMobList();
    ASSERT_LE(3, moblist.size());

    delete &w;
}


TEST (PlayerLogicTest, PlayerMove) {
    DungeonGame::World& w = DungeonGame::World::fromDir(PATH, 0);
    DungeonGame::Player& p = w.getPlayerEnt();

    w.movePlayer('d');
    w.movePlayer('d');
    w.movePlayer('d');
    w.movePlayer('s'); // rotate

    w.movePlayer('s');
    w.movePlayer('s');
    w.movePlayer('s');
    w.movePlayer('s');
    w.movePlayer('s');
    w.movePlayer('s');
    w.movePlayer('d'); // rotate

    w.movePlayer('d');
    w.movePlayer('d');
    w.movePlayer('d');
    w.movePlayer('d');
    w.movePlayer('d');
    w.movePlayer('w'); // rotate
    w.movePlayer('w');

    ASSERT_EQ(make_pair(6u, 10u), p.getPos());

    w.movePlayer('w');
    auto victim = *w.getCurrentLevel().getMob(5, 10);
    ASSERT_EQ(victim.getMaxHp() - p.getAtk(), victim.getHp());

    delete &w;
}


TEST (PlayerLogicTest, PlayerWithering) {
    DungeonGame::World& w = DungeonGame::World::fromDir(PATH, 0);
    DungeonGame::Player& p = w.getPlayerEnt();

    p.setPos(6, 10);
    p.setHp(10); // out of 100
    p.setMana(20); // out of 80

    auto victim = w.getCurrentLevel().getMob(5, 10);
    victim->damage(1000);
    w.processDead();

    ASSERT_EQ((int) (10. + 60*(.2+.05)), p.getHp());
    ASSERT_EQ(20 + 15+5, p.getMana());

    delete &w;
}


TEST (PlayerLogicTest, PlayerCurse) {
    DungeonGame::World& w = DungeonGame::World::fromDir(PATH, 0);
    DungeonGame::Player& p = w.getPlayerEnt();

    p.setPos(6,11);
    p.setMana(2);
    ASSERT_FALSE(p.applyCurse(w.getCurrentLevel())); // not enough mana
    p.setMana(80);
    p.setFacing(DungeonGame::Direction::UP);
    ASSERT_TRUE(p.applyCurse(w.getCurrentLevel()));
    DungeonGame::Mob* victim1 = w.getCurrentLevel().getMob(5, 10);
    DungeonGame::Mob* victim2 = w.getCurrentLevel().getMob(7, 12);
    ASSERT_EQ(60 - (int) (55. * .95), victim1->getHp()); // got hit
    ASSERT_EQ(70, victim2->getHp()); // didn't get hit

    p.setFacing(DungeonGame::Direction::UP);
    p.setPos(7, 11);
    ASSERT_TRUE(p.applyCurse(w.getCurrentLevel()));
    ASSERT_EQ(0, victim1->getHp());
    ASSERT_EQ(70 - (int) (55. * .95), victim2->getHp());

    delete &w;
}


TEST (PlayerLogicTest, PlayerUltimate) {
    DungeonGame::World& w = DungeonGame::World::fromDir(PATH, 0);
    DungeonGame::Player& p = w.getPlayerEnt();

    p.setPos(6, 11);
    p.setMana(79);
    ASSERT_FALSE(p.applyUltimate(w.getCurrentLevel()));
    p.setMana(80);
    DungeonGame::Mob* victim1 = w.getCurrentLevel().getMob(5, 10);
    DungeonGame::Mob* victim2 = w.getCurrentLevel().getMob(7, 12);
    victim1->setMaxHp(1000);
    victim1->setHp(1000);
    victim2->setMaxHp(700);
    victim2->setHp(700);
    ASSERT_TRUE(p.applyUltimate(w.getCurrentLevel()));
    ASSERT_EQ(1000 - (int) (55. * 4.80), victim1->getHp()); // got hit
    ASSERT_EQ(700 - (int) (55. * 4.80), victim2->getHp()); // got hit
    victim1->setHp(1000);
    p.setPos(3,3);
    p.setMana(80);
    ASSERT_TRUE(p.applyUltimate(w.getCurrentLevel()));
    ASSERT_EQ(1000, victim1->getHp());

    delete &w;
}


TEST (PlayerLogicTest, PlayerNecromancy) {
    DungeonGame::World& w = DungeonGame::World::fromDir(PATH, 0);
    DungeonGame::Player& p = w.getPlayerEnt();

    ASSERT_EQ(DungeonGame::ZOMBIE, ((DungeonGame::Undead*) w.getCurrentLevel().getMob(5,10))->getUndeadType());
    p.setPos(7,11);
    p.setFacing(DungeonGame::Direction::RIGHT);
    p.setMana(80);
    DungeonGame::Mob* mob = w.getCurrentLevel().getMob(7, 12);
    uint atk = mob->getAtk();
    uint atkr = mob->getAtkRange();
    ASSERT_FALSE(w.movePlayer(DungeonGame::Controls::TurnToSkeleton));
    mob->damage(1000);
    p.setMana(2);
    ASSERT_FALSE(w.movePlayer(DungeonGame::Controls::TurnToSkeleton));
    p.setMana(80);
    p.setTalentLevel(DungeonGame::NECROMANCY, 1);
    ASSERT_FALSE(w.movePlayer(DungeonGame::Controls::TurnToSkeleton));
    p.setTalentLevel(DungeonGame::NECROMANCY, 4);

    ASSERT_TRUE(w.movePlayer(DungeonGame::Controls::TurnToSkeleton));
    mob = w.getCurrentLevel().getMob(7, 12);
    ASSERT_EQ(mob->getAtk(), atk * p.getTalentConfig().MorphismAtkMul.at(DungeonGame::SKELETON));
    ASSERT_EQ(mob->getAtkRange(), atkr + p.getTalentConfig().MorphismRanges.at(DungeonGame::SKELETON) - 1);
    ASSERT_EQ(DungeonGame::SKELETON, ((DungeonGame::Undead*) mob)->getUndeadType());
    ASSERT_EQ(DungeonGame::ALLIANCE, mob->getFraction());

    delete &w;
}


TEST (PlayerLogicTest, GolemExplode) {
    DungeonGame::World& w = DungeonGame::World::fromDir(PATH, 0);
    DungeonGame::Player& p = w.getPlayerEnt();

    p.setPos(11, 8);
    p.setFacing(DungeonGame::Direction::UP);

    DungeonGame::Mob* mob = w.getCurrentLevel().getMob(9,9);
    mob->setHp(0);
    w.processDead();

    ASSERT_EQ(40, p.getHp());
    ASSERT_EQ(70, w.getCurrentLevel().getMob(7,12)->getHp());
    ASSERT_EQ(DungeonGame::FLOOR, w.getCurrentLevel().getMap()[9][10]);
    ASSERT_EQ(DungeonGame::FLOOR, w.getCurrentLevel().getMap()[10][10]);
    ASSERT_EQ(DungeonGame::FLOOR, w.getCurrentLevel().getMap()[10][11]);
    ASSERT_EQ(DungeonGame::BEDROCK, w.getCurrentLevel().getMap()[8][9]);
    ASSERT_EQ(DungeonGame::BEDROCK, w.getCurrentLevel().getMap()[8][10]);

    delete &w;
}
