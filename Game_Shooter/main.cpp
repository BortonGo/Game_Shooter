#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> 
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sstream> 


int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML Shooter - Step 4: Collision");
    window.setFramerateLimit(60);

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Score
    int score = 0;

    //Font
    sf::Font font;
    if (!font.loadFromFile("arialmt.ttf")) {
        // Вывод ошибки, если шрифт не загрузился
        return -1;
    }

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(20.f, 20.f);
    scoreText.setString("Score: 0");

    // Игрок
    sf::RectangleShape player(sf::Vector2f(50.f, 50.f));
    player.setFillColor(sf::Color::Cyan);
    player.setPosition(935.f, 1000.f);
    float playerSpeed = 8.0f;

    // Пули
    std::vector<sf::RectangleShape> bullets;
    float bulletSpeed = 15.0f;
    sf::Clock shootClock;
    float shootDelay = 0.2f;

    // Враги
    std::vector<sf::RectangleShape> enemies;
    float enemySpeed = 4.0f;
    sf::Clock enemySpawnClock;
    float enemySpawnDelay = 2.0f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        // Управление игроком
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            player.move(-playerSpeed, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            player.move(playerSpeed, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            player.move(0, -playerSpeed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            player.move(0, playerSpeed);

        // Ограничения экрана
        sf::Vector2f pos = player.getPosition();
        if (pos.x < 0) player.setPosition(0, pos.y);
        if (pos.x + player.getSize().x > 1920) player.setPosition(1920 - player.getSize().x, pos.y);
        if (pos.y < 0) player.setPosition(pos.x, 0);
        if (pos.y + player.getSize().y > 1080) player.setPosition(pos.x, 1080 - player.getSize().y);

        // Стрельба
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            if (shootClock.getElapsedTime().asSeconds() > shootDelay) {
                sf::RectangleShape bullet(sf::Vector2f(8.f, 20.f));
                bullet.setFillColor(sf::Color::Yellow);
                sf::Vector2f playerCenter = player.getPosition() + player.getSize() / 2.f;
                bullet.setPosition(playerCenter.x - bullet.getSize().x / 2.f, player.getPosition().y);
                bullets.push_back(bullet);
                shootClock.restart();
            }
        }

        for (auto& bullet : bullets)
            bullet.move(0.f, -bulletSpeed);

        bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
            [](const sf::RectangleShape& b) {
                return b.getPosition().y + b.getSize().y < 0;
            }), bullets.end());

        // Спавн врагов
        if (enemySpawnClock.getElapsedTime().asSeconds() > enemySpawnDelay) {
            sf::RectangleShape enemy(sf::Vector2f(50.f, 50.f));
            enemy.setFillColor(sf::Color::Red);
            float x = static_cast<float>(std::rand() % (1920 - 50));
            enemy.setPosition(x, -60.f);
            enemies.push_back(enemy);
            enemySpawnClock.restart();
        }

        for (auto& enemy : enemies)
            enemy.move(0.f, enemySpeed);

        enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
            [](const sf::RectangleShape& e) {
                return e.getPosition().y > 1080;
            }), enemies.end());

        // === Столкновения пуль с врагами ===
        for (auto bulletIt = bullets.begin(); bulletIt != bullets.end(); ) {
            bool bulletDestroyed = false;
            for (auto enemyIt = enemies.begin(); enemyIt != enemies.end(); ) {
                if (bulletIt->getGlobalBounds().intersects(enemyIt->getGlobalBounds())) {
                    // Столкновение: удаляем пулю и врага
                    enemyIt = enemies.erase(enemyIt);
                    bulletIt = bullets.erase(bulletIt);
                    bulletDestroyed = true;

                    score++;

                    // Обновляем отображаемый текст
                    std::stringstream ss;
                    ss << "Score: " << score;
                    scoreText.setString(ss.str());

                    break;
                }
                else {
                    ++enemyIt;
                }
            }
            if (!bulletDestroyed) {
                ++bulletIt;
            }
        }

        // Отрисовка
        window.clear(sf::Color::Black);
        window.draw(player);
        for (const auto& bullet : bullets)
            window.draw(bullet);
        for (const auto& enemy : enemies)
            window.draw(enemy);
        window.draw(scoreText);
        window.display();
    }

    return 0;
}
