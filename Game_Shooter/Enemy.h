#pragma once
#include <SFML/Graphics.hpp>

class Enemy {
public:
    Enemy(float xPosition);

    void update(float speed);
    void draw(sf::RenderWindow& window) const;

    bool isOffScreen() const;
    sf::FloatRect getBounds() const;

private:
    sf::RectangleShape shape;
};
