#ifndef DINO_HPP
#define DINO_HPP
#include "SFML/Graphics.hpp"
#include "headers/game_object.hpp"

using namespace sf;

class Dino : public GameObject
{
private:
    int vy;
    bool jumping;

public:
    Dino();
    void update();
};

#endif