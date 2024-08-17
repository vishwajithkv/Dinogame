#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP
#include "SFML/Graphics.hpp"
#include "game_object.hpp"

using namespace sf;

class Obstacle : public GameObject
{
public:
    Obstacle(int x);
    void update();
};

#endif