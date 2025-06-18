#include "dino.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

Dino::Dino() : yoshi("assets/image/dinosaur/dino 1.png"), dinosaur(yoshi) // Inicializa dinosaur con la textura
{
    if (!yoshi.loadFromFile("assets/image/dinosaur/dino 1.png")) {
        std::cerr << "No se pudo cargar la textura: assets/image/dinosaur/dino 1.png" << std::endl;
    }
    dinosaur.setTexture(yoshi); // Por si la textura se carga después
    dinosaur.setScale({0.20f, 0.20f});
    dinosaur.setOrigin({0.f, 0.f});
    dinosaur.setPosition({20.f, 223.f});
}

void Dino::draw(sf::RenderWindow& window) {
    window.draw(dinosaur);
}
