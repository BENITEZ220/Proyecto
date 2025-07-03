// Dino.hpp
#ifndef DINO_HPP
#define DINO_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Dino {
public:
    // Constructor
    Dino(const std::string& texturePathPrefix);

    // Updates the animation
    void updateAnimation();

    
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
    sf::Sprite m_sprite;                    
    std::vector<sf::Texture> textures;    
    sf::Clock animationClock;             
    const sf::Time frameDuration;         

    size_t currentFrame;                  
    bool isJumping;                       
    float jumpSpeed;                      
    float gravity;                        
    float originalY;                      

    // Loads all textures for the dinosaur
    bool loadTextures(const std::string& texturePathPrefix);
};

#endif // DINO_HPP
