#ifndef GHOST_HPP
#define GHOST_HPP

#include <SFML/Graphics.hpp>
class Ghost {
private:
    sf::Texture ghost;
    sf::Sprite enemy;
public:
    Ghost();
    void draw(sf::RenderWindow& window);
};
#endif // GHOST_HPP
