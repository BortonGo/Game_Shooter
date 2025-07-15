#include "Player.h"
#include <cstdlib>
#include <iostream>

Player::Player() {
    if (!texture.loadFromFile("player.png")) {
        std::cerr << "Ошибка: не удалось загрузить player.png" << std::endl;
        exit(EXIT_FAILURE);
    }

    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
    sprite.setScale(0.2f, 0.2f);
    sprite.setPosition(935.f, 800.f);

    damaged = false;
    damageCooldown = 1.0f;
    originalPosition = sprite.getPosition();
}

void Player::handleInput(float speed) {
    sf::Vector2f movement(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        movement.x -= speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        movement.x += speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        movement.y -= speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        movement.y += speed;

    sprite.move(movement);

    // Получаем границы спрайта
    sf::FloatRect bounds = sprite.getGlobalBounds();
    sf::Vector2f pos = sprite.getPosition();

    // Проверка границ с учетом размеров
    if (bounds.left < 0)
        sprite.setPosition(bounds.width / 2.f, pos.y);
    if (bounds.left + bounds.width > 1920)
        sprite.setPosition(1920.f - bounds.width / 2.f, pos.y);
    if (bounds.top < 0)
        sprite.setPosition(pos.x, bounds.height / 2.f);
    if (bounds.top + bounds.height > 1080)
        sprite.setPosition(pos.x, 1080.f - bounds.height / 2.f);

    if (!isDamaged())
        originalPosition = sprite.getPosition();
}


void Player::update() {}

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Player::getBounds() const {
    return sprite.getGlobalBounds();
}

sf::Vector2f Player::getPosition() const {
    return sprite.getPosition();
}

sf::Vector2f Player::getCenter() const {
    return sprite.getPosition();
}

void Player::setPosition(const sf::Vector2f& pos) {
    sprite.setPosition(pos);
    originalPosition = pos;
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
        sprite.setPosition(originalPosition + sf::Vector2f(offsetX, offsetY));
    }
    else {
        sprite.setPosition(originalPosition);
    }
}

