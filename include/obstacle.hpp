#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP
#include <SFML/Graphics.hpp>

class Obstacle {
private:
    sf::Texture plant;
    sf::Sprite obstacle;
public:
    Obstacle();
    void draw(sf::RenderWindow& window);
};
#endif // OBSTACLE_HPP