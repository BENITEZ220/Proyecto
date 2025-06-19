#include <SFML/Graphics.hpp>
#include "ground.hpp"
#include "dino.hpp"
#include "obstacle.hpp"
#include "cloud.hpp"
#include "ghost.hpp"

int main()
{
    bool initiated;
    bool presset;
    
    // create the window
    sf::RenderWindow window(sf::VideoMode({800, 400}), "VideoJuego");
    window.setFramerateLimit(30); // Set the frame rate limit to 60 FPS
    presset=false;

    //Dino dino(20, 20);
    Cloud cloud;
    Ghost ghost;
    Ground ground;
    Obstacle obstacle;

    // run the program as long as the window is open
    while (window.isOpen())
    {
        Dino *dino =new Dino(20, 20);
        initiated=false;
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        dino->update();

        if(dino->getLive()) {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)&&!presset) {
                presset=true;
                dino->jump();
                if(!initiated) {
                    initiated=true;
                    dino->initiate();
                }
            }
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)&&!presset) {
                presset=true;
                break;
            }
        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            presset=false;
        }
        // clear the window with black color
        window.clear(sf::Color(135, 206, 235));

        // draw everything here...
        // inside the main loop, between window.clear() and window.display()
        dino->draw(window, sf::RenderStates::Default);
        ghost.draw(window);
        cloud.draw(window);
        obstacle.draw(window);
        ground.draw(window);

        // end the current frame
        window.display();
        delete dino;
    } 
    return 0;
}