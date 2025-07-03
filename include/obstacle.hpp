#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Obstacle {
private:
    sf::Texture plantTexture;
    std::vector<sf::Sprite> obstacles;
    float obstacleSpeed = 6.0f;

public:
    Obstacle() {
        if (!plantTexture.loadFromFile("assets/image/obstacle.png")) {
            throw std::runtime_error("Failed to load obstacle texture");
        }
        for (int i = 0; i < 3; ++i) {
            sf::Sprite obstacle(plantTexture);
            obstacle.scale({0.08f, 0.08f});
            float randomDistance = 300.f + static_cast<float>(rand() % 200);
            obstacle.setPosition({800.f + i * randomDistance, 240.f});
            obstacles.push_back(obstacle);
        }
    }

    void update(bool gameStarted, bool gamePaused) {
        if (!gameStarted || gamePaused) return;
        for (auto& obstacle : obstacles) {
            obstacle.move({-obstacleSpeed, 0.f});
            if (obstacle.getPosition().x < -100) {
                float randomDistance = 300.f + static_cast<float>(rand() % 200);
                obstacle.setPosition({800.f + randomDistance, 240.f});
            }
        }
    }

    void draw(sf::RenderWindow& window) {
        for (const auto& obstacle : obstacles) {
            window.draw(obstacle);
        }
    }

    void reset() {
        for (int i = 0; i < obstacles.size(); ++i) {
            float randomDistance = 300.f + static_cast<float>(rand() % 200);
            obstacles[i].setPosition({800.f + i * randomDistance, 240.f});
        }
    }

    const std::vector<sf::Sprite>& getObstacles() const { return obstacles; }
};
