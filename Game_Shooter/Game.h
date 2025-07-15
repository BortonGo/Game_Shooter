#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    sf::Music backgroundMusic;
    sf::SoundBuffer shootBuffer;
    sf::Sound shootSound;
    sf::SoundBuffer explosionBuffer;
    sf::Sound explosionSound;

    void handleEvents();
    void update();
    void render();
    void checkCollisions();
    void updateTexts();
    void reset();
};
