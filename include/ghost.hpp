#ifndef GHOST_HPP
#define GHOST_HPP
#include <SFML/Graphics.hpp>

class Ghost {
private:
    sf::Texture ghost;
    
public:
    Ghost();
    void draw(sf::RenderWindow& window);
    sf::Sprite enemy;
};
#endif // GHOST_HPP
