#ifndef CLOUD_HPP
#define CLOUD_HPP
#include <SFML/Graphics.hpp>

class Cloud {
private:
    sf::Texture cloud;
    
public:
    Cloud();
    void draw(sf::RenderWindow& window);
    sf::Sprite sky;
};
#endif // CLOUD_HPP
