#include "Enemy.h"

Enemy::Enemy(float x, const sf::Texture& texture) {
    sprite.setTexture(texture);
    sprite.setScale(0.15f, 0.15f); // Подстрой размер при необходимости
    sprite.setPosition(x, -sprite.getGlobalBounds().height);
}

void Enemy::update(float speed) {
    sprite.move(0.f, speed);
}

void Enemy::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

bool Enemy::isOffScreen() const {
    return sprite.getPosition().y > 1080;
}

sf::FloatRect Enemy::getBounds() const {
    sf::FloatRect bounds = sprite.getGlobalBounds();

    // Уменьшаем зону столкновения (по краям отступ 20%)
    float shrinkX = bounds.width * 0.2f;
    float shrinkY = bounds.height * 0.2f;

    bounds.left += shrinkX;
    bounds.top += shrinkY;
    bounds.width -= 2 * shrinkX;
    bounds.height -= 2 * shrinkY;

    return bounds;
}


