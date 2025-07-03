#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Dino.hpp"
#include "Ground.hpp"
#include "Cloud.hpp"
#include "Ghost.hpp"
#include "Obstacle.hpp"
#include <optional>

int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode({800, 400}), "Videojuego");
    window.setFramerateLimit(60);

    // Initialize game entities
    Dino dino;
    Ground ground;
    Cloud cloud;
    Ghost ghost;
    Obstacle obstacle;

    // Title screen
    sf::Texture titleTexture;
    if (!titleTexture.loadFromFile("assets/image/title.png")) {
        return -1;
    }
    sf::Sprite titleSprite(titleTexture);
    titleSprite.setPosition({-20.f, 0.f});
    titleSprite.setScale({0.65f, 0.65f});

    // Background music
    sf::Music backgroundMusic;
    if (!backgroundMusic.openFromFile("assets/audio/melody.mp3")) {
        return -1;
    }
    backgroundMusic.setLoopPoints({sf::milliseconds(500), sf::seconds(2000)});
    backgroundMusic.play();

    // Score text
    sf::Font font;
    if (!font.openFromFile("assets/fonts/font.ttf")) {
        return -1;
    }
    sf::Text metrosText(font);
    metrosText.setString("Score: 0");
    metrosText.setCharacterSize(25);
    metrosText.setFillColor(sf::Color::White);
    metrosText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    metrosText.setPosition({50.f, 10.f});
    int metros = 0;
    int scoreTick = 0;

    bool gameStarted = false;
    bool gamePaused = false;

    // Game loop
    while (window.isOpen()) {
        // Process events
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        // Game start and resume logic
        if (!gameStarted) {
            window.clear(sf::Color(135, 206, 235));
            window.draw(titleSprite);
            window.display();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
                gameStarted = true;
            }
            continue;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            if (gamePaused) {
                gamePaused = false;
                dino.reset();
                obstacle.reset();
                ghost.reset();
                metros = 0;
                metrosText.setString("Score: 0");
            }
        }

        if (gameStarted && !gamePaused) {
            // Update game entities
            dino.update(gameStarted, gamePaused);
            ground.update(gameStarted, gamePaused);
            cloud.update(gameStarted, gamePaused);
            ghost.update(gameStarted, gamePaused);
            obstacle.update(gameStarted, gamePaused);

            // Collision detection
            for (const auto& obs : obstacle.getObstacles()) {
                if (dino.checkCollision(obs)) {
                    gamePaused = true;
                }
            }

            // Score update
            scoreTick++;
            if (scoreTick >= 6) {
                metros++;
                metrosText.setString("Score: " + std::to_string(metros));
                scoreTick = 0;
            }
        }

        // Render
        window.clear(sf::Color(135, 206, 235));
        cloud.draw(window);
        ghost.draw(window);
        ground.draw(window);
        obstacle.draw(window);
        dino.draw(window);
        window.draw(metrosText);
        window.display();
    }

    return 0;
}