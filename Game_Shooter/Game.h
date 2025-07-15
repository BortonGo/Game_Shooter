#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

enum class GameState {
    MENU,
    PLAYING,
    GAME_OVER
};

class Game {
public:
    Game();
    void run();

private:
    sf::RenderWindow window;
    GameState gameState;

    Player player;
    std::vector<Bullet> bullets;
    std::vector<Enemy> enemies;

    float playerSpeed;
    float bulletSpeed;
    float enemySpeed;
    float shootDelay;
    float enemySpawnDelay;
    int score;
    int lives;

    sf::Clock shootClock;
    sf::Clock enemySpawnClock;

    sf::Font font;
    sf::Text menuText;
    sf::Text gameOverText;
    sf::Text scoreText;
    sf::Text livesText;

    sf::Texture asteroidTexture;

    void handleEvents();
    void update();
    void render();
    void checkCollisions();
    void updateTexts();
    void reset();
};
