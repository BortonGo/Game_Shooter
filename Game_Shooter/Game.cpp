#include "Game.h"

Game::Game()
    : window(sf::VideoMode(1920, 1080), "SFML Shooter"), gameState(GameState::MENU),
    playerSpeed(9.0f), bulletSpeed(15.0f), enemySpeed(3.5f),
    shootDelay(0.2f), enemySpawnDelay(2.0f), score(0), lives(3)
{
    window.setFramerateLimit(60);

    font.loadFromFile("arialmt.ttf");

    menuText.setFont(font);
    menuText.setCharacterSize(50);
    menuText.setFillColor(sf::Color::White);
    menuText.setString("PRESS ENTER TO START");
    sf::FloatRect menuBounds = menuText.getLocalBounds();
    menuText.setOrigin(menuBounds.width / 2.f, menuBounds.height / 2.f);
    menuText.setPosition(1920.f / 2.f, 1080.f / 2.f);

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("GAME OVER\nPress R to Restart");
    sf::FloatRect goBounds = gameOverText.getLocalBounds();
    gameOverText.setOrigin(goBounds.width / 2.f, goBounds.height / 2.f);
    gameOverText.setPosition(1920.f / 2.f, 1080.f / 2.f);

    scoreText.setFont(font);
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(20.f, 20.f);

    livesText.setFont(font);
    livesText.setCharacterSize(30);
    livesText.setFillColor(sf::Color::Red);
    livesText.setPosition(1700.f, 20.f);

    updateTexts();
}

void Game::run() {
    while (window.isOpen()) {
        handleEvents();

        if (gameState == GameState::PLAYING) {
            update();
        }

        render();
    }
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }

    if (gameState == GameState::MENU && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        reset();
        gameState = GameState::PLAYING;
    }

    if (gameState == GameState::GAME_OVER && sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        gameState = GameState::MENU;
    }
}

void Game::update() {
    // Управление игроком
    player.handleInput(playerSpeed);

    // Выстрел
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
        shootClock.getElapsedTime().asSeconds() > shootDelay)
    {
        bullets.emplace_back(player.getCenter() - sf::Vector2f(4.f, 20.f));
        shootClock.restart();
    }

    // Обновление пуль
    for (auto& bullet : bullets)
        bullet.update(bulletSpeed);

    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
        [](const Bullet& b) { return b.isOffScreen(); }), bullets.end());

    // Спавн врагов
    if (enemySpawnClock.getElapsedTime().asSeconds() > enemySpawnDelay) {
        float margin = 100.f; // отступ слева и справа
        float x = margin + static_cast<float>(std::rand() % static_cast<int>(1920 - 2 * margin));
        enemies.emplace_back(x);
        enemySpawnClock.restart();
    }

    // Обновление врагов
    for (auto& enemy : enemies)
        enemy.update(enemySpeed);

    // Удаление врагов, долетевших до низа
    for (auto it = enemies.begin(); it != enemies.end(); ) {
        if (it->isOffScreen()) {
            lives--;
            updateTexts();
            it = enemies.erase(it);
        }
        else {
            ++it;
        }
    }

    checkCollisions();
    player.updateDamageEffect();

    if (lives <= 0)
        gameState = GameState::GAME_OVER;
}

void Game::checkCollisions() {
    // Пули + враги
    for (auto bulletIt = bullets.begin(); bulletIt != bullets.end(); ) {
        bool hit = false;
        for (auto enemyIt = enemies.begin(); enemyIt != enemies.end(); ) {
            if (bulletIt->getBounds().intersects(enemyIt->getBounds())) {
                enemyIt = enemies.erase(enemyIt);
                bulletIt = bullets.erase(bulletIt);
                score++;
                updateTexts();
                hit = true;
                break;
            }
            else {
                ++enemyIt;
            }
        }
        if (!hit) ++bulletIt;
    }

    // Враг + игрок
    for (auto it = enemies.begin(); it != enemies.end(); ) {
        if (it->getBounds().intersects(player.getBounds())) {
            if (!player.isDamaged()) {
                player.takeDamage();
                lives--;
                updateTexts();
            }
            it = enemies.erase(it);
        }
        else {
            ++it;
        }
    }
}

void Game::render() {
    window.clear(sf::Color::Black);

    if (gameState == GameState::MENU) {
        window.draw(menuText);
    }
    else if (gameState == GameState::GAME_OVER) {
        window.draw(gameOverText);
    }
    else if (gameState == GameState::PLAYING) {
        player.draw(window);
        for (const auto& bullet : bullets) bullet.draw(window);
        for (const auto& enemy : enemies) enemy.draw(window);
        window.draw(scoreText);
        window.draw(livesText);
    }

    window.display();
}

void Game::updateTexts() {
    scoreText.setString("Score: " + std::to_string(score));
    livesText.setString("Lives: " + std::to_string(lives));
}

void Game::reset() {
    bullets.clear();
    enemies.clear();
    player.setPosition(sf::Vector2f(935.f, 800.f));
    player.resetDamage();
    score = 0;
    lives = 3;
    shootClock.restart();
    enemySpawnClock.restart();
    updateTexts();
}
