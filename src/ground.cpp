#include "ground.h"

Ground::Ground()
{
    line.setSize({800.f, 2.f});
    line.setFillColor(sf::Color::Black);
    line.setPosition({0.f, 350.f});
}

void Ground::draw(sf::RenderWindow& window)
{
    window.draw(line);
}
