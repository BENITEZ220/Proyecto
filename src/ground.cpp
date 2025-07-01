// Ground.cpp
#include "Ground.hpp"
#include <iostream> // For error reporting

Ground::Ground(const std::string& texturePath, float yPosition, float scale, float speed)
    : m_speed(speed)
{
    if (!m_texture.loadFromFile(texturePath)) {
        std::cerr << "Error: Failed to load Ground texture from " << texturePath << std::endl;
        // Handle error
    }
    m_texture.setRepeated(true); // Enable texture repetition for seamless scrolling

    m_sprite1.setTexture(m_texture);
    m_sprite2.setTexture(m_texture);

    m_sprite1.setScale({scale, scale});
    m_sprite2.setScale({scale, scale});

    // Calculate the actual width of the scaled ground texture
    m_width = m_texture.getSize().x * scale;

    m_sprite1.setPosition({0.f, yPosition});
    m_sprite2.setPosition({m_width, yPosition});
}

void Ground::move() {
    m_sprite1.move({-m_speed, 0.f});
    m_sprite2.move({-m_speed, 0.f});

    // Reset position for seamless scrolling
    if (m_sprite1.getPosition().x + m_width < 0) {
        m_sprite1.setPosition({m_sprite2.getPosition().x + m_width, m_sprite1.getPosition().y});
    }
    if (m_sprite2.getPosition().x + m_width < 0) {
        m_sprite2.setPosition({m_sprite1.getPosition().x + m_width, m_sprite2.getPosition().y});
    }
}

void Ground::draw(sf::RenderWindow& window) const {
    window.draw(m_sprite1);
    window.draw(m_sprite2);
}
