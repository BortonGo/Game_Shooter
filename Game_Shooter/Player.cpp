#include "Player.h"
#include <cstdlib>

Player::Player() {
    shape.setSize(sf::Vector2f(50.f, 50.f));
    shape.setFillColor(sf::Color::Cyan);
    shape.setPosition(935.f, 800.f);

    damaged = false;
    damageCooldown = 1.0f;
    originalPosition = shape.getPosition();
}

void Player::handleInput(float speed) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        shape.move(-speed, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        shape.move(speed, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        shape.move(0, -speed);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        shape.move(0, speed);

    // Ограничения экрана
    sf::Vector2f pos = shape.getPosition();
    if (pos.x < 0) shape.setPosition(0, pos.y);
    if (pos.x + shape.getSize().x > 1920) shape.setPosition(1920 - shape.getSize().x, pos.y);
    if (pos.y < 0) shape.setPosition(pos.x, 0);
    if (pos.y + shape.getSize().y > 1080) shape.setPosition(pos.x, 1080 - shape.getSize().y);

    // Сохраняем позицию только если НЕ в состоянии урона
    if (!isDamaged()) {
        originalPosition = shape.getPosition();
    }
}

void Player::update() {
    // пусто пока
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

sf::FloatRect Player::getBounds() const {
    return shape.getGlobalBounds();
}

sf::Vector2f Player::getPosition() const {
    return shape.getPosition();
}

void Player::setPosition(const sf::Vector2f& pos) {
    shape.setPosition(pos);
    originalPosition = pos;
}

sf::Vector2f Player::getCenter() const {
    return shape.getPosition() + shape.getSize() / 2.f;
}

bool Player::isDamaged() const {
    return damaged && damageClock.getElapsedTime().asSeconds() < damageCooldown;
}

void Player::resetDamage() {
    damaged = false;
}

void Player::takeDamage() {
    damaged = true;
    damageClock.restart();
}

void Player::updateDamageEffect() {
    if (isDamaged()) {
        float offsetX = static_cast<float>((std::rand() % 7) - 3);
        float offsetY = static_cast<float>((std::rand() % 7) - 3);
        shape.setPosition(originalPosition + sf::Vector2f(offsetX, offsetY));
    }
    
}