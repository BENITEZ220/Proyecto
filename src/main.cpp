#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <optional>
#include <vector>
#include <string>

int main()
{
    // Animation variables
    size_t currentFrame = 0;
    sf::Clock animationClock;
    const sf::Time frameDuration = sf::milliseconds(100); // 100 ms per frame

    // Create the main window
    sf::RenderWindow window(sf::VideoMode({800, 400}), "Videojuego");
    window.setFramerateLimit(60);

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
    dinosaur.scale({0.25f, 0.25f}); // Cambia el tamaño del dinosaurio
    dinosaur.setPosition({20.f, 200.f}); // Cambia la posición del dinosaurio

    // Obstáculo
    sf::Texture plant("assets/image/obstacle.png");
    sf::Sprite obstacle(plant);
    obstacle.scale({0.10f, 0.10f});
    obstacle.setPosition({650.f, 220.f});
    float obstacleSpeed = 2.5f;

    // Suelo
    sf::Texture groundTexture("assets/image/ground.png");
    groundTexture.setRepeated(true);

    sf::Sprite ground1(groundTexture), ground2(groundTexture);

    ground1.setScale({0.30f, 0.30f});
    ground2.setScale({0.30f, 0.30f});

    const float groundWidth = groundTexture.getSize().x * 0.10f;
    ground1.setPosition({0.f, 80.f});
    ground2.setPosition({groundWidth, 80.f});

    float groundSpeed = 2.5f;

    // Nube
    sf::Texture cloudTexture("assets/image/cloud.jpg");
    sf::Sprite sky(cloudTexture);
    sky.scale({1.5f, 1.f});
    sky.setPosition({0.f, 0.f});

    float cloudSpeed = 1.5f;

    // Fantasma
    sf::Texture ghostTexture("assets/image/ghost.png");
    sf::Sprite enemy(ghostTexture);
    enemy.scale({0.10f, 0.10f});
    enemy.setPosition({-1200.f, 150.f});

    float ghostSpeed = 4.5f;

    std::vector<sf::Sprite> obstacles;
    for (int i = 0; i < 3; ++i) { // Reduce el número de obstáculos a 3
        sf::Sprite obstacle(plant);
        obstacle.scale({0.10f, 0.10f});
        float randomDistance = 300.f + static_cast<float>(rand() % 200); // Distancia aleatoria entre 300 y 500
        obstacle.setPosition({800.f + i * randomDistance, 220.f});
        obstacles.push_back(obstacle);
    }

    // Loop del juego
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

        // Suelo
        ground1.move({-groundSpeed, 0.f});
        ground2.move({-groundSpeed, 0.f});

        if (ground1.getPosition().x + groundWidth < 0)
            ground1.setPosition({ground2.getPosition().x + groundWidth, ground1.getPosition().y});

        if (ground2.getPosition().x + groundWidth < 0)
            ground2.setPosition({ground1.getPosition().x + groundWidth, ground2.getPosition().y});

        // Obstáculos
        for (auto& obstacle : obstacles) {
            obstacle.move({-obstacleSpeed, 0.f});
            if (obstacle.getPosition().x < -100) {
                float randomDistance = 300.f + static_cast<float>(rand() % 200); // Distancia aleatoria entre 300 y 500
                obstacle.setPosition({800.f + randomDistance, 220.f});
            }
        }

        // Enemy
        enemy.move({-ghostSpeed, 0.f});
        if (enemy.getPosition().x < -2000)
        {
            enemy.setPosition({800.f, 150.f});
        }

        // Clear screen
        window.clear(sf::Color(135, 206, 235));

        // Draw the sprite
        window.draw(sky);
        window.draw(enemy);
        window.draw(ground1);
        window.draw(ground2);
        for (const auto& obstacle : obstacles) {
            window.draw(obstacle);
        }
        window.draw(dinosaur);

        // Update the window
        window.display();
    }

    return 0;
}
