// Obstacle.cpp
#include "Obstacle.hpp"
#include <cstdlib> // For rand()
#include <iostream> // For error reporting

Obstacle::Obstacle(const std::string& texturePath, float initialX, float initialY, float speed)
    : m_speed(speed)
{
    if (!m_texture.loadFromFile(texturePath)) {
        std::cerr << "Error: Failed to load Obstacle texture from " << texturePath << std::endl;
        // Handle error
    }
    m_sprite.setTexture(m_texture);
    m_sprite.scale({0.08f, 0.08f}); // Reduce obstacle size
    m_sprite.setPosition({initialX, initialY});
}

void Obstacle::move() {
    m_sprite.move({-m_speed, 0.f});
}

void Obstacle::resetPosition(float windowWidth) {
    float randomDistance = 300.f + static_cast<float>(rand() % 200); // Random distance between 300 and 500
    m_sprite.setPosition({windowWidth + randomDistance, m_sprite.getPosition().y});
}

sf::FloatRect Obstacle::getGlobalBounds() const {
    sf::FloatRect bounds = m_sprite.getGlobalBounds();
    bounds.width *= 0.8f;  // Reduce width by 20%
    bounds.height *= 0.8f; // Reduce height by 20%
    return bounds;
}

void Obstacle::draw(sf::RenderWindow& window) const {
    window.draw(m_sprite);
}

float Obstacle::getPositionX() const {
    return m_sprite.getPosition().x;
}
