#include "Enemy.h"

Enemy::Enemy(float xPosition) {
    shape.setSize(sf::Vector2f(50.f, 50.f));
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(xPosition, -60.f); // немного выше экрана
}

void Enemy::update(float speed) {
    shape.move(0.f, speed);
}

void Enemy::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}

bool Enemy::isOffScreen() const {
    return shape.getPosition().y > 1080;
}

sf::FloatRect Enemy::getBounds() const {
    return shape.getGlobalBounds();
}
