#ifndef DINO_HPP
#define DINO_HPP
#include <SFML/Graphics.hpp>

class Dino {
private:
    sf::Texture yoshi;
    sf::Sprite dinosaur;
public:
    Dino();
    void draw(sf::RenderWindow& window);
};
#endif // DINO_HPP