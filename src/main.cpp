#include <SFML/Graphics.hpp>
#include <ground.h>
#include "obstacle.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 500}), "VIDEOJUEGO");

    Ground ground;
    Obstacle obstacle;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color::White);
        ground.draw(window);
        obstacle.draw(window);
        window.display();
    }
}