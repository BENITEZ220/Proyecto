// Dino.hpp
#ifndef DINO_HPP
#define DINO_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Dino {
public:
    // Constructor: loads textures and initializes the dinosaur sprite
    Dino(const std::string& texturePathPrefix);

    // Updates the animation frame of the dinosaur
    void updateAnimation();

    // Initiates a jump for the dinosaur
    void jump();

    // Updates the dinosaur's position during a jump, applying gravity
    void updateJump();

    // Resets the dinosaur's position and state for a new game
    void reset();

    // Sets the texture to indicate a collision
    void setCollisionTexture();

    // Gets the global bounding box of the dinosaur for collision detection
    sf::FloatRect getGlobalBounds() const;

    // Draws the dinosaur sprite to the render window
    void draw(sf::RenderWindow& window) const;

    // Gets the current position of the dinosaur
    sf::Vector2f getPosition() const;

    // Sets the position of the dinosaur
    void setPosition(const sf::Vector2f& pos);

    // Checks if the dinosaur is currently jumping
    bool isJumpingState() const;

private:
    sf::Sprite m_sprite;                    // The sprite representing the dinosaur
    std::vector<sf::Texture> m_textures;    // Vector to hold animation frames
    sf::Clock m_animationClock;             // Clock to manage animation frame timing
    const sf::Time m_frameDuration;         // Duration for each animation frame

    size_t m_currentFrame;                  // Current frame index for animation
    bool m_isJumping;                       // Flag to indicate if the dinosaur is jumping
    float m_jumpSpeed;                      // Current vertical speed during jump
    float m_gravity;                        // Gravity applied during jump
    float m_originalY;                      // Original Y position of the dinosaur (ground level)

    // Loads all necessary textures for the dinosaur
    bool loadTextures(const std::string& texturePathPrefix);
};

#endif // DINO_HPP
