#include "headers/obstacle.hpp"
#include "headers/constants.hpp"
#include "SFML/Graphics.hpp"

using namespace sf;

string getObstructionAssetPath()
{
    return "assets/imgs/cactus.png";
}

Obstacle::Obstacle(int x) : GameObject(x, SCREEN_HEIGHT - GROUND_HEIGHT - OBSTACLE_HEIGHT, getObstructionAssetPath(), OBSTACLE_WIDTH, OBSTACLE_HEIGHT)
{
}

void Obstacle::update()
{
    x -= OBSTACLE_SPEED;
    sprite.setPosition(x, y);
}