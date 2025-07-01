// Dino.cpp
#include "Dino.hpp"
#include <iostream> // For error reporting

Dino::Dino(const std::string& texturePathPrefix)
    : m_frameDuration(sf::milliseconds(100)),
      m_currentFrame(0),
      m_isJumping(false),
      m_jumpSpeed(-10.0f), // Initial jump velocity
      m_gravity(0.3f),     // Gravity strength
      m_originalY(200.f)   // Default ground Y position
{
    if (!loadTextures(texturePathPrefix)) {
        std::cerr << "Error: Failed to load Dino textures." << std::endl;
        // Handle error, maybe throw an exception or set a flag
    }

    m_sprite.setTexture(m_textures[0]);
    m_sprite.scale({0.25f, 0.25f});
    m_sprite.setPosition({20.f, m_originalY});
}

bool Dino::loadTextures(const std::string& texturePathPrefix) {
    m_textures.resize(9);
    for (int i = 0; i < 6; ++i) {
        if (!m_textures[i].loadFromFile(texturePathPrefix + "dino " + std::to_string(i + 1) + ".png")) {
            return false;
        }
    }
    if (!m_textures[6].loadFromFile(texturePathPrefix + "dino down.png") ||
        !m_textures[7].loadFromFile(texturePathPrefix + "dino loose.png") ||
        !m_textures[8].loadFromFile(texturePathPrefix + "dino up.png")) {
        return false;
    }
    return true;
}

void Dino::updateAnimation() {
    if (m_animationClock.getElapsedTime() >= m_frameDuration) {
        m_currentFrame = (m_currentFrame + 1) % 5; // Cycle through frames 0-4 for running animation
        m_sprite.setTexture(m_textures[m_currentFrame]);
        m_animationClock.restart();
    }
}

void Dino::jump() {
    if (!m_isJumping) {
        m_isJumping = true;
        m_jumpSpeed = -10.0f; // Reset jump speed for a new jump
    }
}

void Dino::updateJump() {
    if (m_isJumping) {
        m_sprite.setTexture(m_textures[8]); // Show 'dino up' image while jumping
        m_sprite.move({0.f, m_jumpSpeed});
        m_jumpSpeed += m_gravity;

        if (m_sprite.getPosition().y >= m_originalY) {
            m_sprite.setPosition({m_sprite.getPosition().x, m_originalY});
            m_isJumping = false;
            m_jumpSpeed = -10.0f; // Reset jump speed for next jump
        }
    }
}

void Dino::reset() {
    m_sprite.setTexture(m_textures[0]); // Reset to initial texture
    m_sprite.setPosition({20.f, m_originalY}); // Reset dinosaur position
    m_isJumping = false;
    m_jumpSpeed = -10.0f;
    m_currentFrame = 0;
    m_animationClock.restart();
}

void Dino::setCollisionTexture() {
    m_sprite.setTexture(m_textures[7]); // Show 'dino loose' image on collision
}

sf::FloatRect Dino::getGlobalBounds() const {
    sf::FloatRect bounds = m_sprite.getGlobalBounds();
    bounds.size *= 0.8f;  // Reduce width by 20%
    bounds.height *= 0.8f; // Reduce height by 20%
    return bounds;
}

void Dino::draw(sf::RenderWindow& window) const {
    window.draw(m_sprite);
}

sf::Vector2f Dino::getPosition() const {
    return m_sprite.getPosition();
}

void Dino::setPosition(const sf::Vector2f& pos) {
    m_sprite.setPosition(pos);
}

bool Dino::isJumpingState() const {
    return m_isJumping;
}
