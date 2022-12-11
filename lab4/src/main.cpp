#include <SFML/Graphics.hpp>

#include "World.h"
#include "Player.h"

#include "TileMap.h"
#include "input.h"

#include <sstream>
#include <unistd.h>


using namespace DungeonGame;


static const string levels_path = "../../lab4/levels";
static const string tileset_path = "../../lab4/assets/tileset/tileset_16x16.png";
static const string font_path = "../../lab4/assets/fonts/solo5.ttf";
static const uint font_size = 14;
static const float scale = 4.f;
static const string window_title = "Necromancer: ";
static const string wrap = "+========================================================================================+\n";


static const sf::Vector2i tileSize(16, 16);


void render(sf::RenderWindow& window, sf::Texture& texture, sf::Text& text, World& w) {
    TileMap tileMap(texture, text, tileSize, scale);
    tileMap.load(w);
    window.clear();
    tileMap.drawTiles(window);
    tileMap.drawPlayer(window);
    tileMap.drawMobs(window);
    tileMap.drawTexts(window);
    window.display();
}


char get_input(sf::RenderWindow& window) {
    sf::Event event{};
    do {
        window.pollEvent(event);
        if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Tilde)
            return '`';
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code <= sf::Keyboard::Z)
                return 'a' + event.key.code;
            else return '0' + event.key.code;
        }
    } while (true);
}


void save_dialog(World& w) {
    char choice;
    uint save_number;
    system("clear 2>/dev/null");

    cout << wrap << "\n\t\t\tSave data to:\n\t" << w.getSavePath() << "\t? \n\n" << wrap << "\n\t\t[y: yes / N: no / c: change save path]:  " << endl;
    cin >> choice;

    if (choice == 'y') w.savePlayerData();
    else if (choice == 'c') {
        cout << "Save number:  ";
        Input::input(save_number);
        ostringstream stream;
        stream << w.getLevelDir() << "/save" << save_number << ".ini";
        w.setSavePath(stream.str());
        try {
            w.savePlayerData();
            cout << "Saved to slot " << save_number << endl;
        } catch (exception& e) {
            cout << "Could not save to slot " << save_number << ":  " << e.what() << endl;
        }

    }
}


void talent_dialog(World& w) {
    static const Talent talent_by_num[] {WITHERING, CURSE, NECROMANCY, MORPHISM, ULTIMATE};

    int choice = 0;
    while (true) {
        system("clear 2>/dev/null");
        Player &p = w.getPlayerEnt();
        const TalentConfig &tc = p.getTalentConfig();
        uint max_levels_by_num[]{tc.WitheringMaxLevel, tc.CurseMaxLevel, tc.NecromancyMaxLevel, tc.MorphismMaxLevel,
                                 tc.UltimateMaxLevel};

        cout << wrap << "\n\t\t\tPlayer stats"
                        "\n\n\tLevel:     " << p.getLevel() << "   (" << p.getExp() << " / " << tc.ExpPerLevel << " exp)"
                                                                                                                "\n\tMax HP:    "
             << p.getMaxHp() <<
             "\n\tMax Mana:  " << p.getMaxMana() <<
             "\n\tATK:       " << p.getAtk() << endl << endl;
        cout << wrap << "\n\t\t\tTalents upgrade (available points: " << p.getTalentPoints() << ")"
                                                                                                "\n\n\t1. Withering (level "
             << p.getTalentLevel(WITHERING) << " / " << tc.WitheringMaxLevel << ")"
                                                                                "\n\t2. Curse (level "
             << p.getTalentLevel(CURSE) << " / " << tc.CurseMaxLevel << ")"
                                                                        "\n\t3. Necromancy (level "
             << p.getTalentLevel(NECROMANCY) << " / " << tc.NecromancyMaxLevel << ")"
                                                                                  "\n\t4. Morphism (level "
             << p.getTalentLevel(MORPHISM) << " / " << tc.MorphismMaxLevel << ")"
                                                                              "\n\t5. Ultimate (level "
             << p.getTalentLevel(ULTIMATE) << " / " << tc.UltimateMaxLevel << ")"
                                                                              "\n\n\t0. back" << endl << endl;
        Input::getNumInRange(choice, 0, 5);

        if (choice == 0) return;
        Talent tal = talent_by_num[choice - 1];
        uint max_level = max_levels_by_num[choice - 1];
        if (p.getTalentPoints() <= 0) cout << "-   Not enough talent points!" << endl;
        else if (p.getTalentLevel(tal) >= max_level) cout << "-   This talent is at Max level!" << endl;
        else {
            p.setTalentPoints(p.getTalentPoints() - 1);
            p.setTalentLevel(tal, p.getTalentLevel(tal) + 1);
            cout << "+   Talent upgraded!   +" << endl;
        }
        sleep(1);
    };

}



int setup(string& filename, uint& save_num) {
    int choice = 0;
    system("clear 2>/dev/null");
    cout << wrap <<
           "\n\t\t   The Necromancer Game\n\n\n\t\t"
           "     (1) PLAY '" << filename << "' (save slot " << save_num << ")\n\n\t\t"
           "     (2) SELECT LEVEL\n\n\t\t"
           "     (3) QUIT\n\n" << wrap << endl;
    Input::getNumInRange(choice, 1, 3);
    if (choice == 1) return 0;
    else if(choice == 3) exit(0);
    else if(choice == 2) {
        system("clear 2>/dev/null");
        cout << "\n\tAvailable levels: " << endl;
        chdir(levels_path.c_str());
        system("ls -1d */");
        cout << "\n\tEnter level name: " << ends;
        cin >> filename;
        system("clear 2>/dev/null");
        if (chdir(filename.c_str()) == EXIT_SUCCESS) {
            cout << "Existing save files: " << endl;
            system("ls -1 save*.ini");
        }
        cout << "\n\tEnter save number: " << ends;
        cin >> save_num;
        return 0;
    }

}


int main()
{
    chdir(levels_path.c_str());
    string filename = "t_corpus";
    char choice;
    bool has_moved;
    uint save_number = 0;
    uint cur_level = 0;

    sf::VideoMode vm(1, 1);
    sf::RenderWindow window(vm, window_title);
    window.setVerticalSyncEnabled(true);
    window.close();

    sf::Texture texture;
    texture.loadFromFile(tileset_path);
    sf::Text text;
    sf::Font font;
    font.loadFromFile(font_path);
    text.setFont(font);
    text.setCharacterSize(font_size);

    do {
        setup(filename, save_number);
        try {
            cout << "\n\t\tLoading from '" << filename << "', save file save" << save_number << ".ini" << endl;
            sleep(1);
            World& w = World::fromDir(levels_path + "/" + filename, save_number);
            cur_level = w.getCurrentLevel().getLevelNumber();

            // restart window
            vm = sf::VideoMode(w.getCurrentLevel().getMapSize().second * tileSize.x * scale, w.getCurrentLevel().getMapSize().first * tileSize.y * scale);
            window.create(vm, window_title + w.getCurrentLevel().getLevelTitle());
            while (w.isGameRunning() && window.isOpen()) {
                if (cur_level < w.getCurrentLevel().getLevelNumber()) {
                    // close window
                    window.close();
                    save_dialog(w);
                    // restart window
                    window.create(vm, window_title + w.getCurrentLevel().getLevelTitle());
                    cur_level = w.getCurrentLevel().getLevelNumber();
                }
                // render
                render(window, texture, text, w);
                // get input
                choice = get_input(window);
                // if input `: exit to main menu
                if (choice == '`') {
                    window.close();
                    break;
                }
                    // if input P: close, save dialog, reopen
                else if (choice == 'p') {
                    window.close();
                    save_dialog(w);
                    window.create(vm, window_title + w.getCurrentLevel().getLevelTitle());
                }  // if input T: talents menu
                else if (choice == 't') {
                    window.close();
                    talent_dialog(w);
                    window.create(vm, window_title + w.getCurrentLevel().getLevelTitle());
                }
                else if (choice == 'r') {
                    // if input R: restart level
                    w.loadLevel(cur_level);
                    w.loadPlayerData();
                    w.getPlayerEnt().setHp(w.getPlayerEnt().getMaxHp());
                    w.getPlayerEnt().setMana(0);
                }
                else {
                    has_moved = w.movePlayer(choice);
                    render(window, texture, text, w);
                    if (has_moved && w.isGameRunning()) {
                        w.processDead();
                        w.moveMobs();
                        w.processDead();
                        w.doSpawnCycle();
                    }
                    auto player_pos = w.getPlayerEnt().getPos();
                    if (cur_level < w.getLevelCount() - 1 && w.getCurrentLevel().getMap()[player_pos.first][player_pos.second] == DungeonGame::LADDER_DOWN) {
                        window.clear();
                        window.close();
                        w.loadLevel(cur_level + 1);
                        vm = sf::VideoMode(w.getCurrentLevel().getMapSize().second * tileSize.x * scale, w.getCurrentLevel().getMapSize().first * tileSize.y * scale);
                        window.create(vm, window_title + w.getCurrentLevel().getLevelTitle());
                    }
                }
            }

            // close window
            if (!w.isGameRunning()) {
                render(window, texture, text, w);
                sleep(2);
                window.close();
                system("clear 2>/dev/null");
                if (w.getPlayerEnt().getHp() > 0) {
                    cout << wrap <<
                            "\n\t\t\t\t\t\tYou win!"
                            "\n\n\tYour excellency, the great lord Necromancer, you have gloriously beaten this dungeon!"
                            "\nThis adventure shall be transcribed into the world history. Now, countless nations across"
                            "\nthe globe will praise your courage, and so you will be named the real Dungeon Master!" <<
                         "\n\n" << wrap << endl;
                }
                else {
                    cout << wrap <<
                            "\n\t\t\t\t\t\tSo sorry!"
                            "\n\tYou have been defeated by the countless dangers and traps"
                            "\nfollowing you along this dungeon. Let us try again, my lord Necromancer? " <<
                            "\n\n\tJust load from your save data! The last slot used was " << save_number
                            << "\n\n" << wrap << endl;
                }
                for (int i = 0; i < 8; i++) {
                    sleep(1);
                    cout << '.' << ends;
                }
                cout << endl;
            }

        } catch (exception& e) {
            cout << "\n\t\tUnexpected outcome...  " << e.what() << endl;
            window.close();
            sleep(1);
            continue;
        }

    } while (choice != 3);

    return 0;
}
