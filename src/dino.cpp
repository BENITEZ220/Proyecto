#include "dino.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

Dino::Dino(int x, int y) : states(9), sprite(states[0]) {
    initiated = false;
    live = true;
    state = 0;
    timerState = 10;
    states.resize(9);

    if (!states[0].loadFromFile("assets/image/dinosaur/dino 1.png")) {
        std::cout << "No se pudo cargar la textura: assets/image/dino1.png" << '\n';
    } 
    if (!states[1].loadFromFile("assets/image/dinosaur/dino 2.png")) {
        std::cout << "No se pudo cargar la textura: assets/image/dino2.png" << '\n';
    } 
    if (!states[2].loadFromFile("assets/image/dinosaur/dino 3.png")) {
        std::cout << "No se pudo cargar la textura: assets/image/dino3.png" << '\n';
    }
    if (!states[3].loadFromFile("assets/image/dinosaur/dino 4.png")) {
        std::cout << "No se pudo cargar la textura: assets/image/dino4.png" << '\n';
    }
    if (!states[4].loadFromFile("assets/image/dinosaur/dino 5.png")) {
        std::cout << "No se pudo cargar la textura: assets/image/dino5.png" << '\n';
    }
    if (!states[5].loadFromFile("assets/image/dinosaur/dino 6.png")) {
        std::cout << "No se pudo cargar la textura: assets/image/dino6.png" << '\n';
    }
    if (!states[6].loadFromFile("assets/image/dinosaur/dino down.png")) {
        std::cout << "No se pudo cargar la textura: assets/image/dino down.png" << '\n';
    }
    if (!states[7].loadFromFile("assets/image/dinosaur/dino up.png")) {
        std::cout << "No se pudo cargar la textura: assets/image/dino up.png" << '\n';
    }
    if (!states[8].loadFromFile("assets/image/dinosaur/dino loose.png")) {
        std::cout << "No se pudo cargar la textura: assets/image/dino loose.png" << '\n';
    }
    sprite.setTexture(states[state]);
    sprite.setOrigin({0.f, 0.f});
    sprite.setPosition({100.f, 100.f});
    sprite.setScale({1.f, 1.f});
    move = 0.0f;

}

void Dino::update() {

    timerState--; 

    if(!jumpState) {
        if (timerState == 0) {
            state++;
            state %= (6);
            sprite.setTexture(states[state]);
            //auto bounds = sprite.getLocalBounds();
            sprite.setOrigin({0.f, 0.f});
            timerState = 10;
        }

    } else {
        if (state != 7) {
            state = 7; 
            sprite.setTexture(states[state]);
            //auto bounds = sprite.getLocalBounds();
            sprite.setOrigin({0.f, 0.f});
            timerState = 10;
        }   
    }

    if(!initiated)return;

}

void Dino::jump() {
    if (live) {
        jumpState = true;
    }
}

sf::Vector2f Dino::getPosition() {
    return sprite.getPosition();
}

bool Dino::getLive() {
    return live;
}

void Dino::death() {
    live = false;
    sprite.setTexture(states[8]);
}
void Dino::initiate() {
    initiated = true;
}

void Dino::draw(sf::RenderTarget &rt, sf::RenderStates rs) const{
    rt.draw(sprite,rs);
}



