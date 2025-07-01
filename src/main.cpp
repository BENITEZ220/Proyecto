// main.cpp
#include <SFML/Graphics.hpp>
#include <optional>
#include <vector>
#include <string>
#include <cstdlib> 
#include <ctime>  

// Include our new class headers
#include "Dino.hpp"
#include "Obstacle.hpp"
#include "Ground.hpp"
#include "Ghost.hpp"

int main()
{
    // Seed the random number generator
    srand(static_cast<unsigned int>(time(0)));

    // Create the main window
    sf::RenderWindow window(sf::VideoMode({800, 400}), "Videojuego");
    window.setFramerateLimit(60);

    // Game state variables
    bool gameStarted = false;
    bool gamePaused = false;

    // --- Game Objects Initialization ---
    // Dinosaur
    Dino dinosaur("assets/image/dinosaur/"); // Pass the prefix path to Dino constructor

    // Obstacles
    std::vector<Obstacle> obstacles;
    float obstacleSpeed = 3.5f; // Increased obstacle speed
    for (int i = 0; i < 3; ++i) { // Reduce the number of obstacles to 3
        float randomDistance = 300.f + static_cast<float>(rand() % 200); // Random distance between 300 and 500
        obstacles.emplace_back("assets/image/obstacle.png", 800.f + i * randomDistance, 240.f, obstacleSpeed);
    }

    // Ground
    Ground ground("assets/image/ground.png", 80.f, 0.30f, 3.5f); // yPosition, scale, speed

    // Cloud (Sky background) - remains a simple sprite as it doesn't need complex logic
    sf::Texture cloudTexture;
    if (!cloudTexture.loadFromFile("assets/image/cloud.jpg")) {
        return -1;
    }
    sf::Sprite sky(cloudTexture);
    sky.scale({1.5f, 1.f});
    sky.setPosition({0.f, 0.f});

    // Ghost (Enemy)
    Ghost ghost("assets/image/ghost.png", -1200.f, 150.f, 4.5f); // initialX, initialY, speed

    // --- Game Loop ---
    while (window.isOpen())
    {
        // Process events
        while (const std::optional<sf::Event> event = window.pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Game start and resume logic
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            if (!gameStarted) {
                gameStarted = true;
            } else if (gamePaused) {
                gamePaused = false;
                dinosaur.reset(); // Reset dinosaur state
                for (auto& obstacle : obstacles) {
                    obstacle.resetPosition(800.f); // Reset obstacle positions
                }
                ghost.resetPosition(800.f); // Reset ghost position
            }
        }

        if (gameStarted && !gamePaused) {
            // Update game objects
            dinosaur.updateAnimation();

            // Jumping logic
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !dinosaur.isJumpingState()) {
                dinosaur.jump();
            }
            dinosaur.updateJump();

            ground.move(); // Move ground

            // Obstacles
            for (auto& obstacle : obstacles) {
                obstacle.move();
                if (obstacle.getPositionX() < -100) {
                    obstacle.resetPosition(800.f);
                }
            }

            // Ghost
            ghost.move();
            if (ghost.getPositionX() < -2000) { // If ghost goes far off screen
                ghost.resetPosition(800.f);
            }

            // Collision detection
            for (const auto& obstacle : obstacles) {
                if (dinosaur.getGlobalBounds().findIntersection(obstacle.getGlobalBounds())) {
                    dinosaur.setCollisionTexture(); // Show collision texture
                    gamePaused = true;
                }
            }
        }

        // Clear screen
        window.clear(sf::Color(135, 206, 235)); // Sky blue background

        // Draw game objects
        window.draw(sky);
        ghost.draw(window);
        ground.draw(window);
        for (const auto& obstacle : obstacles) {
            obstacle.draw(window);
        }
        dinosaur.draw(window);

        // Update the window
        window.display();
    }

    return 0;
}
