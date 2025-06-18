#include "obstacle.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

Obstacle::Obstacle():plant("assets/image/obstacle.png"),obstacle(plant) 
{
    if (!plant.loadFromFile("assets/image/obstacle.png")) {
        std::cerr << "No se pudo cargar la textura" << std::endl;
    }
    obstacle.setTexture(plant); // Por si la textura se carga después
    obstacle.scale({0.10f, 0.10f});
    obstacle.setPosition({650.f, 220.f});
}

void Obstacle::draw(sf::RenderWindow& window) {
    window.draw(obstacle);
}