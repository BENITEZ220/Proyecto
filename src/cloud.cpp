#include "cloud.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

Cloud::Cloud() : cloud("assets/image/cloud.jpg"),sky(cloud) {

    if (cloud.loadFromFile("assets/image/cloud.jpg")) {
        sky.setTexture(cloud);
    }   
    // Nube
    sky.scale({1.5f, 1.f});
    sky.setPosition({0.f, 0.f});

}

void Cloud::draw(sf::RenderWindow& window) {
    window.draw(sky);
}
