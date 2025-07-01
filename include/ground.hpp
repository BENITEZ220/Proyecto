// Ground.hpp
#ifndef GROUND_HPP
#define GROUND_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Ground {
public:
    // Constructor: loads texture and initializes two sprites for seamless scrolling
    Ground(const std::string& texturePath, float yPosition, float scale, float speed);

    // Moves the ground sprites horizontally and resets their position for seamless scrolling
    void move();

    // Draws both ground sprites to the render window
    void draw(sf::RenderWindow& window) const;

private:
    sf::Texture m_texture;  // The texture for the ground
    sf::Sprite m_sprite1;   // First sprite for scrolling ground
    sf::Sprite m_sprite2;   // Second sprite for scrolling ground
    float m_speed;          // Horizontal speed of the ground
    float m_width;          // Width of a single ground sprite after scaling
};

#endif // GROUND_HPP
