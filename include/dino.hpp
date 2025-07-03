#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>

class Dino {
private:
    std::vector<sf::Texture> yoshiFrames;
    sf::Sprite sprite;
    sf::SoundBuffer jumpBuffer;
    sf::Sound jumpSound;
    sf::SoundBuffer loseBuffer;
    sf::Sound gameover;
    size_t currentFrame = 0;
    sf::Clock animationClock;
    const sf::Time frameDuration = sf::milliseconds(100);
    bool isJumping = false;
    float jumpSpeed = -10.0f;
    float gravity = 0.3f;
    float originalY = 200.f;

public:
    Dino() {
        yoshiFrames.resize(9);
        for (int i = 0; i < 6; ++i) {
            if (!yoshiFrames[i].loadFromFile("assets/image/dinosaur/dino " + std::to_string(i + 1) + ".png")) {
                throw std::runtime_error("Failed to load dino texture " + std::to_string(i + 1));
            }
        }
        if (!yoshiFrames[6].loadFromFile("assets/image/dinosaur/dino down.png") ||
            !yoshiFrames[7].loadFromFile("assets/image/dinosaur/dino loose.png") ||
            !yoshiFrames[8].loadFromFile("assets/image/dinosaur/dino up.png")) {
            throw std::runtime_error("Failed to load dino texture");
        }
        sprite.setTexture(yoshiFrames[0]);
        sprite.scale({0.25f, 0.25f});
        sprite.setPosition({20.f, 200.f});
        if (!jumpBuffer.loadFromFile("assets/audio/jump.mp3")) {
            throw std::runtime_error("Failed to load jump sound");
        }
        jumpSound.setBuffer(jumpBuffer);
        if (!loseBuffer.loadFromFile("assets/audio/gameover.mp3")) {
            throw std::runtime_error("Failed to load gameover sound");
        }
        gameover.setBuffer(loseBuffer);
        gameover.setVolume(700.f);
    }

    void update(bool gameStarted, bool gamePaused) {
        if (!gameStarted || gamePaused) return;

        // Animation
        if (animationClock.getElapsedTime() >= frameDuration) {
            currentFrame = (currentFrame + 1) % 5;
            sprite.setTexture(yoshiFrames[currentFrame]);
            animationClock.restart();
        }

        // Jumping logic
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !isJumping) {
            isJumping = true;
            jumpSound.play();
        }
        if (isJumping) {
            sprite.setTexture(yoshiFrames[8]);
            sprite.move({0.f, jumpSpeed});
            jumpSpeed += gravity;
            if (sprite.getPosition().y >= originalY) {
                sprite.setPosition({sprite.getPosition().x, originalY});
                isJumping = false;
                jumpSpeed = -10.0f;
            }
        }

        // Crouching logic
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && !isJumping) {
            sprite.setTexture(yoshiFrames[6]);
            sprite.setScale({0.25f, 0.25f});
            sprite.setPosition({20.f, 230.f});
        } else if (!isJumping) {
            sprite.setTexture(yoshiFrames[currentFrame]);
            sprite.setScale({0.25f, 0.25f});
            sprite.setPosition({sprite.getPosition().x, originalY});
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }

    bool checkCollision(const sf::Sprite& obstacle) {
        sf::FloatRect dinosaurBox = sprite.getGlobalBounds();
        sf::FloatRect obstacleBox = obstacle.getGlobalBounds();
        dinosaurBox.size *= 0.8f;
        obstacleBox.size *= 0.8f;
        if (dinosaurBox.findIntersection(obstacleBox)) {
            sprite.setTexture(yoshiFrames[7]);
            gameover.play();
            return true;
        }
        return false;
    }

    void reset() {
        sprite.setTexture(yoshiFrames[0]);
        sprite.setPosition({20.f, 200.f});
        isJumping = false;
        jumpSpeed = -10.0f;
        currentFrame = 0;
        animationClock.restart();
    }

    sf::Sprite& getSprite() { return sprite; }
};