#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Bullet {
public:
    Bullet(const sf::Vector2f& position);

    void update(float speed);
    void draw(sf::RenderWindow& window) const;

    bool isOffScreen() const;
    sf::FloatRect getBounds() const;

private:
    sf::RectangleShape shape;
};
