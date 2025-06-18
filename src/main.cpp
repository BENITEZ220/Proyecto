#include <SFML/Graphics.hpp>
#include "ground.hpp"
#include "dino.hpp"
#include "obstacle.hpp"
#include "cloud.hpp"
#include "ghost.hpp"

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode({800, 400}), "VideoJuego");
    window.setFramerateLimit(30); // Set the frame rate limit to 60 FPS

    Dino dino;
    Cloud cloud;
    Ghost ghost;
    Ground ground;
    Obstacle obstacle;

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color(135, 206, 235));

        // draw everything here...
        // window.draw(...);
        // inside the main loop, between window.clear() and window.display()
        ghost.draw(window);
        cloud.draw(window);
        obstacle.draw(window);
        ground.draw(window);
        dino.draw(window);

        // end the current frame
        window.display();
    }

    return 0;
}