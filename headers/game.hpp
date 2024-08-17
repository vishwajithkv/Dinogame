#ifndef GAME_HPP
#define GAME_HPP

#include "dino.hpp"
#include "obstacle.hpp"
#include "SFML/Graphics.hpp"

using namespace std;
using namespace sf;

class Game
{
private:
    int score, bonus, highScore, obstacleGap;
    bool gameOver;

    RenderWindow window;
    Dino dino;
    vector<Obstacle *> obstacles;

    void handleEvents();
    void update();
    void render();
    void reset();
    void deleteObstacles();

public:
    Game();
    void run();
};

bool isColliding(Dino &dino, Obstacle &obstacle);

#endif