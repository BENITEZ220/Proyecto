#include "ghost.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

Ghost::Ghost() : ghost("assets/image/ghost.png"), enemy(ghost) 
{
    if (ghost.loadFromFile("assets/image/ghost.png")) {
        enemy.setTexture(ghost);
    }
    
    enemy.scale({0.10f, 0.10f});
    enemy.setPosition({-1200.f, 150.f});
}

void Ghost::draw(sf::RenderWindow& window) {

}
