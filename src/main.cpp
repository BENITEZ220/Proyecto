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

    if (!yoshiFrames[6].loadFromFile("assets/image/dinosaur/dino down.png") ||
        !yoshiFrames[7].loadFromFile("assets/image/dinosaur/dino loose.png") ||
        !yoshiFrames[8].loadFromFile("assets/image/dinosaur/dino up.png")) {
        return -1; // Exit if any texture fails to load
    }

    // Create sprite and set initial texture
    sf::Sprite dinosaur(yoshiFrames[0]);
    dinosaur.scale({0.25f, 0.25f}); // Cambia el tamaño del dinosaurio
    dinosaur.setPosition({20.f, 200.f}); // Cambia la posición del dinosaurio

    // Obstáculo
    sf::Texture plant("assets/image/obstacle.png");
    sf::Sprite obstacle(plant);
    obstacle.scale({0.08f, 0.08f}); // Reduce obstacle size
    obstacle.setPosition({650.f, 240.f}); // Move obstacle 5 pixels lower
    float obstacleSpeed = 6.0f; // Increased obstacle speed
    float groundSpeed = obstacleSpeed; // Ground moves at the same speed as obstacles

    // Suelo
    sf::Texture groundTexture("assets/image/ground.png");
    groundTexture.setRepeated(true);

    sf::Sprite ground1(groundTexture), ground2(groundTexture);

    ground1.setScale({0.30f, 0.30f});
    ground2.setScale({0.30f, 0.30f});

    const float groundWidth = groundTexture.getSize().x * 0.10f;
    ground1.setPosition({0.f, 80.f});
    ground2.setPosition({groundWidth, 80.f});

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
        obstacle.scale({0.08f, 0.08f}); // Reduce obstacle size
        float randomDistance = 300.f + static_cast<float>(rand() % 200); // Distancia aleatoria entre 300 y 500
        obstacle.setPosition({800.f + i * randomDistance, 240.f}); // Move obstacles 5 pixels lower
        obstacles.push_back(obstacle);
    }

    bool isJumping = false;
    float jumpSpeed = -10.0f; // Further reduced jump speed for lower jump
    float gravity = 0.3f; // Increased gravity for faster fall
    float originalY = dinosaur.getPosition().y;

    bool gameStarted = false;
    bool gamePaused = false;

    // Pantalla de título
    sf::Texture titleTexture;
    if (!titleTexture.loadFromFile("assets/image/title.png")) {
        return -1;
    }
    sf::Sprite titleSprite(titleTexture);
    titleSprite.setPosition({-20.f,0.f}); // Ajusta la posición si lo deseas
    titleSprite.setScale({0.65f, 0.65f}); // Ajusta el tamaño de la pantalla de título

    // Música de fondo
    sf::Music backgroundMusic;
    if (!backgroundMusic.openFromFile("assets/audio/melody.mp3")) {
        return -1;
    }
    backgroundMusic.setLoopPoints({sf::milliseconds(500), sf::seconds(2000)}); // Asegura que la música se repita infinitamente
    backgroundMusic.play();

    // Sonido de salto
    sf::SoundBuffer jumpBuffer("assets/audio/jump.mp3");
    sf::Sound jumpSound(jumpBuffer);

    // Sonido de muerte
    sf::SoundBuffer losseBuffer("assets/audio/gameover.mp3");
    sf::Sound gameover(losseBuffer);
    gameover.setVolume(700.f); // Volumen 
 
    

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

        // Game start and resume logic
        if (!gameStarted) {
            // Mostrar pantalla de título
            window.clear(sf::Color(135, 206, 235));
            window.draw(titleSprite);
            window.display();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
                gameStarted = true;
            }
            continue;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            if (!gameStarted) {
                gameStarted = true;
            } else if (gamePaused) {
                gamePaused = false;
                dinosaur.setTexture(yoshiFrames[0]); // Reset to initial texture
                dinosaur.setPosition({20.f, 200.f}); // Reset dinosaur position
                for (auto& obstacle : obstacles) {
                    float randomDistance = 300.f + static_cast<float>(rand() % 200); // Reset obstacle positions
                    obstacle.setPosition({800.f + randomDistance, 240.f});
                }
                enemy.setPosition({-1200.f, 150.f}); // Reset enemy position
            }
        }

        if (gameStarted && !gamePaused) {
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
                    obstacle.setPosition({800.f + randomDistance, 240.f}); // Move obstacles 5 pixels lower
                }
            }

            // Enemy
            enemy.move({-ghostSpeed, 0.f});
            if (enemy.getPosition().x < -2000)
            {
                enemy.setPosition({800.f, 150.f});
            }

            // Jumping logic
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !isJumping) {
                isJumping = true;
                jumpSound.play(); // Reproducir sonido de salto
            }

            if (isJumping) {
                dinosaur.setTexture(yoshiFrames[8]); // Show 'dino up' image while jumping
                dinosaur.move({0.f, jumpSpeed});
                jumpSpeed += gravity;

                if (dinosaur.getPosition().y >= originalY) {
                    dinosaur.setPosition({dinosaur.getPosition().x, originalY});
                    isJumping = false;
                    jumpSpeed = -10.0f; // Reset jump speed
                }
            }
            
            // Crouching logic
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && !isJumping) {
                dinosaur.setTexture(yoshiFrames[6]); // Show 'dino down' image
                dinosaur.setScale({0.25f, 0.25f}); // Adjust scale for crouching
                dinosaur.setPosition({20.f , 230.f }); // Lower position slightly
            } else if (!isJumping) {
                dinosaur.setTexture(yoshiFrames[currentFrame]); // Reset to running animation
                dinosaur.setScale({0.25f, 0.25f}); // Reset scale
                dinosaur.setPosition({dinosaur.getPosition().x, originalY}); // Reset position
            }

            // Collision detection
            for (const auto& obstacle : obstacles) {
                sf::FloatRect dinosaurBox = dinosaur.getGlobalBounds();
                sf::FloatRect obstacleBox = obstacle.getGlobalBounds();

                // Reduce the size of the bounding boxes
                dinosaurBox.size *= 0.8f; // Reduce width by 20%
                obstacleBox.size *= 0.8f; // Reduce height by 20%

                if (dinosaurBox.findIntersection(obstacleBox)) {
                    dinosaur.setTexture(yoshiFrames[7]); // Show collision texture
                    gamePaused = true;
                    gameover.play(); // Play game over sound
                }
            }
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
