#ifndef GROUND_HPP
#define GROUND_HPP
#include <SFML/Graphics.hpp>

class Ground {
private:
    sf::Texture floor;
    sf::Sprite ground;
public:
    Ground();
    void draw(sf::RenderWindow& window);
};
#endif // GROUND_HPP
