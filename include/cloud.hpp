#pragma once
#include <SFML/Graphics.hpp>

class Cloud {
private:
    sf::Texture cloudTexture;
    sf::Sprite sky;
    float cloudSpeed = 1.5f;

public:
    Cloud() {
        if (!cloudTexture.loadFromFile("assets/image/cloud.jpg")) {
            throw std::runtime_error("Failed to load cloud texture");
        }
        sky.setTexture(cloudTexture);
        sky.scale({1.5f, 1.f});
        sky.setPosition({0.f, 0.f});
    }

    void update(bool gameStarted, bool gamePaused) {
        if (!gameStarted || gamePaused) return;
        // No movement for sky/cloud as in original code
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sky);
    }
};