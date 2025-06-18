#include "cloud.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

Cloud::Cloud() : cloud("assets/image/cloud.png"), sky(cloud) {
    if (!cloud.loadFromFile("assets/image/cloud.png")) {
        std::cerr << "No se pudo cargar la textura: assets/image/cloud.png" << std::endl;
    }
    sky.setTexture(cloud);
    sky.setScale({0.30f, 0.30f});
    sky.setOrigin({0.f, 0.f});
    sky.setPosition({20.f, 20.f});
}

void Cloud::draw(sf::RenderWindow& window) {
    window.draw(sky);
}
