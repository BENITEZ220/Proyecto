// Ghost.hpp
#ifndef GHOST_HPP
#define GHOST_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Ghost {
public:
    // Constructor: loads texture and initializes the ghost sprite
    Ghost(const std::string& texturePath, float initialX, float initialY, float speed);

    // Moves the ghost horizontally based on its speed
    void move();

    // Resets the ghost's position to the right of the screen
    void resetPosition(float windowWidth);

    // Draws the ghost sprite to the render window
    void draw(sf::RenderWindow& window) const;

private:
    sf::Sprite m_sprite;    // The sprite representing the ghost
    sf::Texture m_texture;  // The texture for the ghost
    float m_speed;          // Horizontal speed of the ghost
};

#endif // GHOST_HPP

