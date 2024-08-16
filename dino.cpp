#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "headers/constants.h"
#include "headers/player.cpp"
#include "headers/game.cpp"
   
// The collide method for the dino class
bool Dino::collide(Obstacle &obstacle)
{
    return (x + DINO_WIDTH > obstacle.getX() && x < obstacle.getX() + OBSTACLE_WIDTH &&
            y + DINO_HEIGHT > obstacle.getY() && y < obstacle.getY() + OBSTACLE_HEIGHT);
}

int main()
{
    Game game;  // Create a game object
    game.run(); // Run the game loop
    return 0;   // Return 0 when the program ends
}
