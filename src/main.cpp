#include <SFML/Graphics.hpp>

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode({800, 400}), "Video Juego");
    window.setFramerateLimit(30); // Set the frame rate limit to 60 FPS

    sf::Texture plant("assets/obstacle.png");
    sf::Sprite obstacle(plant);
    obstacle.scale({0.10f, 0.10f});
    obstacle.setPosition({650.f, 220.f});

    sf::Texture floor("assets/ground.png");
    sf::Sprite ground(floor);
    ground.scale({0.30f, 0.30f});
    ground.setOrigin({0.f, 0.f});
    ground.setPosition({0.f, 80.f});

    sf::Texture yoshi("assets/dinosaur/dino 1.png");
    sf::Sprite dinosaur(yoshi);
    dinosaur.scale({0.20f, 0.20f});
    dinosaur.setOrigin({0.f, 0.f});
    dinosaur.setPosition({20.f, 223.f});

    sf::Texture cloud("assets/cloud.png");
    sf::Sprite sky(cloud);
    sky.scale({0.30f, 0.30f});
    sky.setOrigin({0.f, 0.f});
    sky.setPosition({20.f, 20.f});

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
        window.draw(sky);
        window.draw(dinosaur);
        window.draw(obstacle);
        window.draw(ground);

        // end the current frame
        window.display();
    }

    return 0;
}