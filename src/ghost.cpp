// Ghost.cpp
#include "Ghost.hpp"
#include <iostream> // For error reporting

Ghost::Ghost(const std::string& texturePath, float initialX, float initialY, float speed)
    : m_speed(speed)
{
    if (!m_texture.loadFromFile(texturePath)) {
        std::cerr << "Error: Failed to load Ghost texture from " << texturePath << std::endl;
        // Handle error
    }
    m_sprite.setTexture(m_texture);
    m_sprite.scale({0.10f, 0.10f});
    m_sprite.setPosition({initialX, initialY});
}

void Ghost::move() {
    m_sprite.move({-m_speed, 0.f});
}

void Ghost::resetPosition(float windowWidth) {
    m_sprite.setPosition({windowWidth, m_sprite.getPosition().y});
}

void Ghost::draw(sf::RenderWindow& window) const {
    window.draw(m_sprite);
}
