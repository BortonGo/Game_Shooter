#pragma once
#include <SFML/Graphics.hpp>

class Enemy {
public:
    Enemy(float x, const sf::Texture& texture);
    void update(float speed);
    void draw(sf::RenderWindow& window) const;
    bool isOffScreen() const;
    sf::FloatRect getBounds() const;

private:
    sf::Sprite sprite;
};