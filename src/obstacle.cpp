#include "obstacle.h"
#include <iostream>

Obstacle::Obstacle()
    : texture(), sprite(texture)
{
    if (!texture.loadFromFile("assets/obstacle.png")) {
        std::cerr << "No se pudo cargar la textura: assets/ground.png" << std::endl;
    }
    sprite.setPosition(sf::Vector2f(400.f, 300.f)); // Puedes ajustar la posición
}

void Obstacle::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}