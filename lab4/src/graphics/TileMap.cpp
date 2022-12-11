#include "TileMap.h"
#include "TileCoords.h"

#include <sstream>


TileMap::TileMap(const sf::Texture& texture, const sf::Text& text, const sf::Vector2i& tileSize, float scale)
        : m_texture(texture), m_text(text), m_tileSize(tileSize), m_scale(scale) {}


static const map<DungeonGame::Fraction, sf::Color> fracColors {
        {DungeonGame::ALLIANCE, sf::Color::Cyan},
        {DungeonGame::BANDITS, sf::Color::Yellow},
        {DungeonGame::GOBLINS, sf::Color::Green},
        {DungeonGame::ABYSS, sf::Color::Magenta},
};


void TileMap::load(DungeonGame::World& w) {
    DungeonGame::Level& map = w.getCurrentLevel();
    DungeonGame::Player& p = w.getPlayerEnt();

    const int height = map.getMapSize().first;
    const int width = map.getMapSize().second;

    m_vertices.resize(width * height * 4);

    for (int x = 0; x < height; ++x) {
        for (int y = 0; y < width; ++y)
        {
            const DungeonGame::Cell tile = map.getMap()[x][y];
            const pair<int, int> coords = tile_coords.at(tile);
            const float tu = coords.first, tv = coords.second;

            sf::Vertex* quad = &m_vertices[(y + x * width) * 4];

            quad[0].position = sf::Vector2f((y + 0.f) * m_tileSize.x * m_scale, (x + 0.f) * m_tileSize.y * m_scale);
            quad[1].position = sf::Vector2f((y + 1.f) * m_tileSize.x * m_scale, (x + 0.f) * m_tileSize.y * m_scale);
            quad[2].position = sf::Vector2f((y + 1.f) * m_tileSize.x * m_scale, (x + 1.f) * m_tileSize.y * m_scale);
            quad[3].position = sf::Vector2f((y + 0.f) * m_tileSize.x * m_scale, (x + 1.f) * m_tileSize.y * m_scale);

            quad[0].texCoords = sf::Vector2f(tu, tv);
            quad[1].texCoords = sf::Vector2f(tu + m_tileSize.x, tv);
            quad[2].texCoords = sf::Vector2f(tu + m_tileSize.x, tv + m_tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu, tv + m_tileSize.y);
        }
    }

    sf::Text text(m_text);
    ostringstream status;
    status << "HP: " << w.getPlayerEnt().getHp() << " / " << w.getPlayerEnt().getMaxHp() << "    "
           << "Mana: " << w.getPlayerEnt().getMana() << " / " << w.getPlayerEnt().getMaxMana();
    text.setString(status.str());
    text.setFillColor(fracColors.at(w.getPlayerEnt().getFraction()));
    m_texts.push_back(text);

    m_player = sf::Sprite(m_texture);
    pair<int, int> coords = player_tile_coords.at(w.getPlayerEnt().getFacing());
    int tu = coords.first, tv = coords.second;
    m_player.setTextureRect({ tu, tv, w.getPlayerEnt().getFacing() != DungeonGame::LEFT ? m_tileSize.x : -m_tileSize.x, m_tileSize.y});
    m_player.setPosition(w.getPlayerEnt().getPos().second * m_tileSize.x * m_scale, w.getPlayerEnt().getPos().first * m_tileSize.y * m_scale);
    if (w.getPlayerEnt().getHp() == 0) {
        m_player.setOrigin(0, m_tileSize.y);
        m_player.setRotation(90.f);
    }
    m_player.scale(m_scale, m_scale);

    for (auto& mob: w.getCurrentLevel().getMobList()) {
        sf::Sprite sprite(m_texture);
        sf::Text mob_text(m_text);
        ostringstream mob_status;
        mob_status << " (" << mob->getHp() << " / " << mob->getMaxHp() << ")";
        mob_text.setString(mob_status.str());
        mob_text.setFillColor(fracColors.at(mob->getFraction()));
        mob_text.setPosition(mob->getPos().second * m_tileSize.x * m_scale, mob->getPos().first * m_tileSize.y * m_scale);
        switch (mob->getType()) {
            case DungeonGame::MORTAL:
                coords = mortal_tile_coords.at(mob->getFacing());
                break;
            case DungeonGame::UNDEAD:
                coords = undead_tile_coords.at(make_pair(((DungeonGame::Undead*) mob)->getUndeadType(), mob->getFacing()));
                break;
            case DungeonGame::GOLEM:
                coords = golem_tile_coords.at(((DungeonGame::Golem*) mob)->getGolemType());
                break;
            default:;
        }
        tu = coords.first, tv = coords.second;
        sprite.setTextureRect({tu, tv, mob->getFacing() != DungeonGame::LEFT ? m_tileSize.x : -m_tileSize.x, m_tileSize.y});
        sprite.setPosition(mob->getPos().second * m_tileSize.x * m_scale, mob->getPos().first * m_tileSize.y * m_scale);
        if (mob->getHp() == 0) {
            sprite.setOrigin(0, m_tileSize.y);
            sprite.setRotation(90.f);
        }
        sprite.scale(m_scale, m_scale);
        m_mobs.push_back(sprite);
        m_texts.push_back(mob_text);
    }

}

void TileMap::drawTiles(sf::RenderWindow &window) const {
    window.draw(m_vertices.data(), m_vertices.size(), sf::Quads, &m_texture);
}

void TileMap::drawPlayer(sf::RenderWindow &window) const {
    window.draw(m_player);
}

void TileMap::drawMobs(sf::RenderWindow &window) const {
    for (const auto& s: m_mobs)
        window.draw(s);
}

void TileMap::drawTexts(sf::RenderWindow &window) const {
    for (const auto& t: m_texts)
        window.draw(t);
}

