#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SFML/Graphics.hpp>

class Obstacle {
private:
    sf::Texture texture;
    sf::Sprite sprite;
public:
    Obstacle(); // Constructor sin parámetros
    void draw(sf::RenderWindow& window);
};

#endif // OBSTACLE_H
