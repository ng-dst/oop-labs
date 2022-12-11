#ifndef OOP_TILEMAP_H
#define OOP_TILEMAP_H

#include "SFML/Graphics.hpp"

#include "World.h"


class TileMap {
public:
    TileMap(const sf::Texture& texture, const sf::Text& text, const sf::Vector2i& tileSize, float scale=2.);

    void load(DungeonGame::World& w);

    void drawTiles(sf::RenderWindow& window) const;
    void drawPlayer(sf::RenderWindow& window) const;
    void drawMobs(sf::RenderWindow& window) const;
    void drawTexts(sf::RenderWindow& window) const;

private:
    float m_scale;
    const sf::Texture& m_texture;
    const sf::Text& m_text;
    sf::Sprite m_player;
    list<sf::Sprite> m_mobs;
    list<sf::Text> m_texts;
    sf::Vector2i m_tileSize;
    std::vector<sf::Vertex> m_vertices;

};


#endif //OOP_TILEMAP_H
