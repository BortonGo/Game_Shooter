#include "Bullet.h"

Bullet::Bullet(const sf::Vector2f& position) {
    shape.setSize(sf::Vector2f(8.f, 20.f));
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(position);
}

void Bullet::update(float speed) {
    shape.move(0.f, -speed);
}

void Bullet::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}

bool Bullet::isOffScreen() const {
    return shape.getPosition().y + shape.getSize().y < 0;
}

sf::FloatRect Bullet::getBounds() const {
    return shape.getGlobalBounds();
}
