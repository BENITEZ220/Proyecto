#include "ghost.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

Ghost::Ghost() : ghost("assets/image/ghost.png"), enemy(ghost) {
    if (!ghost.loadFromFile("assets/image/ghost.png")) {
        std::cerr << "No se pudo cargar la textura: assets/image/ghost.png" << std::endl;
    }
    enemy.setTexture(ghost);
    enemy.setScale({0.10f, 0.10f});
    enemy.setOrigin({0.f, 0.f});
    enemy.setPosition({200.f, 150.f});
}

void Ghost::draw(sf::RenderWindow& window) {
    window.draw(enemy);
}
