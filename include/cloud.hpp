#ifndef CLOUD_HPP
#define CLOUD_HPP
#include <SFML/Graphics.hpp>

class Cloud {
private:
    sf::Texture cloud;
    sf::Sprite sky;
public:
    Cloud();
    void draw(sf::RenderWindow& window);
};
#endif // CLOUD_HPP
