#ifndef GROUND_H
#define GROUND_H

#include <SFML/Graphics.hpp>

class Ground
{
private:
    sf::RectangleShape line;

public:
    Ground(); // Constructor
    void draw(sf::RenderWindow& window); // Método para dibujar el suelo
};

#endif // GROUND_H
