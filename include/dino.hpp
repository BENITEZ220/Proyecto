#ifndef DINO_HPP
#define DINO_HPP
#include <iostream>
#include <SFML/Graphics.hpp>

class Dino {
private:

    bool live;
    bool initiated;
    bool jumpState;
    int state;
    int timerState;
    std::vector<sf::Texture> states;
    sf::Sprite sprite;
    float move;

public:
    Dino(int,int);
    void update();
    void jump();
    sf::Vector2f getPosition();
    bool getLive();
    void death();
    void initiate();
    virtual void draw(sf::RenderTarget&, sf::RenderStates)const;

    
};
#endif // DINO_HPP