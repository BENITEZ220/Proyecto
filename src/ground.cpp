#include "ground.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

Ground::Ground() : floor("assets/image/ground.png"), ground(floor) 
{
    if (!floor.loadFromFile("assets/image/ground.png")) {
        std::cerr << "No se pudo cargar la textura" << std::endl;
    }
    ground.setTexture(floor); // Por si la textura se carga después
    ground.scale({0.30f, 0.30f});
    ground.setOrigin({0.f, 0.f});
    ground.setPosition({0.f, 80.f});
}

void Ground::draw(sf::RenderWindow& window) {
    window.draw(ground);
}