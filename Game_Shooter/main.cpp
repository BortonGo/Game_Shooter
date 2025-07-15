#include <SFML/Graphics.hpp>
#include <vector>

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML Shooter - Step 2: Shooting");
    window.setFramerateLimit(60);

    // Игрок
    sf::RectangleShape player(sf::Vector2f(50.f, 50.f));
    player.setFillColor(sf::Color::Cyan);
    player.setPosition(935.f, 1000.f);

    float playerSpeed = 8.0f;

    // Пули
    std::vector<sf::RectangleShape> bullets;
    float bulletSpeed = 15.0f;

    // Задержка между выстрелами
    sf::Clock shootClock;
    float shootDelay = 0.2f; // 200 мс

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Управление игроком
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            player.move(-playerSpeed, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            player.move(playerSpeed, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            player.move(0, -playerSpeed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            player.move(0, playerSpeed);

        // Границы
        sf::Vector2f pos = player.getPosition();
        if (pos.x < 0) player.setPosition(0, pos.y);
        if (pos.x + player.getSize().x > 1920) player.setPosition(1920 - player.getSize().x, pos.y);
        if (pos.y < 0) player.setPosition(pos.x, 0);
        if (pos.y + player.getSize().y > 1080) player.setPosition(pos.x, 1080 - player.getSize().y);

        // Стрельба по пробелу
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

        // Обновление пуль
        for (auto& bullet : bullets)
            bullet.move(0.f, -bulletSpeed);

        // Удаление вышедших пуль
        bullets.erase(
            std::remove_if(bullets.begin(), bullets.end(), [](const sf::RectangleShape& b) {
                return b.getPosition().y + b.getSize().y < 0;
                }),
            bullets.end()
        );

        // Отрисовка
        window.clear(sf::Color::Black);
        window.draw(player);
        for (const auto& bullet : bullets)
            window.draw(bullet);
        window.display();
    }

    return 0;
}
