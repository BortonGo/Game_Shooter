#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Player {
public:
    Player();

    void handleInput(float speed);
    void update();
    void draw(sf::RenderWindow& window);
    void takeDamage();

    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f& pos);
    sf::Vector2f getCenter() const;

    bool isDamaged() const;
    void resetDamage();
    void updateDamageEffect();

private:
    sf::Texture texture;
    sf::Sprite sprite;

    bool damaged;
    sf::Clock damageClock;
    float damageCooldown;
    sf::Vector2f originalPosition;
};

