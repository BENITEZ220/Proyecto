#pragma once
#include <SFML/Graphics.hpp>

class Ground {
private:
    sf::Texture groundTexture;
    sf::Sprite ground1, ground2;
    float groundSpeed = 6.0f;
    float groundWidth;

public:
    Ground() {
        if (!groundTexture.loadFromFile("assets/image/ground.png")) {
            throw std::runtime_error("Failed to load ground texture");
        }
        groundTexture.setRepeated(true);
        ground1.setTexture(groundTexture);
        ground2.setTexture(groundTexture);
        ground1.setScale({0.30f, 0.30f});
        ground2.setScale({0.30f, 0.30f});
        groundWidth = groundTexture.getSize().x * 0.10f;
        ground1.setPosition({0.f, 80.f});
        ground2.setPosition({groundWidth, 80.f});
    }

    void update(bool gameStarted, bool gamePaused) {
        if (!gameStarted || gamePaused) return;
        ground1.move({-groundSpeed, 0.f});
        ground2.move({-groundSpeed, 0.f});
        if (ground1.getPosition().x + groundWidth < 0) {
            ground1.setPosition({ground2.getPosition().x + groundWidth, ground1.getPosition().y});
        }
        if (ground2.getPosition().x + groundWidth < 0) {
            ground2.setPosition({ground1.getPosition().x + groundWidth, ground2.getPosition().y});
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(ground1);
        window.draw(ground2);
    }
};