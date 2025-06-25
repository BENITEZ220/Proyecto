#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
 
int main()
{
    // Animation variables
    size_t currentFrame = 0;
    sf::Clock animationClock;
    const sf::Time frameDuration = sf::milliseconds(100); // 100 ms per frame

    // Create the main window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Videojuego");

    // Load textures for animation frames
    std::vector<sf::Texture> yoshiFrames(9);
    for (int i = 0; i < 6; ++i)
    {
        if (!yoshiFrames[i].loadFromFile("assets/image/dinosaur/dino " + std::to_string(i + 1) + ".png"))
        {
            return -1; // Exit if any texture fails to load
        }
    }

    // Create sprite and set initial texture
    sf::Sprite dinosaur(yoshiFrames[0]);



    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        while (const std::optional<sf::Event> event = window.pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Update animation
        if (animationClock.getElapsedTime() >= frameDuration)
        {
            currentFrame = (currentFrame + 1) % 5; // Cycle through frames
            dinosaur.setTexture(yoshiFrames[currentFrame]);
            animationClock.restart();
        }

        // Clear screen
        window.clear();

        // Draw the sprite
        window.draw(dinosaur);

        // Update the window
        window.display();
    }
}
