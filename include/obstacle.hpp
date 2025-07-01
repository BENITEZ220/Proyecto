// Obstacle.hpp
#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Obstacle {
public:
    // Constructor: loads texture and initializes the obstacle sprite
    Obstacle(const std::string& texturePath, float initialX, float initialY, float speed);

    // Moves the obstacle horizontally based on its speed
    void move();

    // Resets the obstacle's position to the right of the screen
    void resetPosition(float windowWidth);

    // Gets the global bounding box of the obstacle for collision detection
    sf::FloatRect getGlobalBounds() const;

    // Draws the obstacle sprite to the render window
    void draw(sf::RenderWindow& window) const;

    // Gets the current X position of the obstacle
    float getPositionX() const;

private:
    sf::Sprite m_sprite;    // The sprite representing the obstacle
    sf::Texture m_texture;  // The texture for the obstacle
    float m_speed;          // Horizontal speed of the obstacle
};

#endif // OBSTACLE_HPP
