#pragma once
#include <SFML/Graphics.hpp>

class Ghost {
private:
    sf::Texture ghostTexture;
    sf::Sprite enemy;
    float ghostSpeed = 4.5f;

public:
    Ghost() {
        if (!ghostTexture.loadFromFile("assets/image/ghost.png")) {
            throw std::runtime_error("Failed to load ghost texture");
        }
        enemy.setTexture(ghostTexture);
        enemy.scale({0.10f, 0.10f});
        enemy.setPosition({-1200.f, 150.f});
    }

    void update(bool gameStarted, bool gamePaused) {
        if (!gameStarted || gamePaused) return;
        enemy.move({-ghostSpeed, 0.f});
        if (enemy.getPosition().x < -2000) {
            enemy.setPosition({800.f, 150.f});
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(enemy);
    }

    void reset() {
        enemy.setPosition({-1200.f, 150.f});
    }

    sf::Sprite& getSprite() { return enemy; }
};

