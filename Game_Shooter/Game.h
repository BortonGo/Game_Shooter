#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include <vector>
#include <sstream>

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
    void handleEvents();
    void update();
    void render();

    void reset();
    void spawnEnemy();
    void checkCollisions();
    void updateTexts();

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

    sf::Clock shootClock;
    sf::Clock enemySpawnClock;

    // UI
    int score;
    int lives;
    sf::Font font;
    sf::Text menuText;
    sf::Text gameOverText;
    sf::Text scoreText;
    sf::Text livesText;
};
