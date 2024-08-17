#include "headers/dino.hpp"
#include "headers/constants.hpp"
#include "SFML/Graphics.hpp"

using namespace sf;

Dino::Dino() : GameObject(100, SCREEN_HEIGHT - GROUND_HEIGHT - DINO_HEIGHT, "assets/imgs/dino.png", DINO_WIDTH, DINO_HEIGHT)
{
    this->vy = 0;
    this->jumping = false;
}

void Dino::update()
{
    if (Keyboard::isKeyPressed(Keyboard::Space) && !jumping)
    {
        vy = -JUMP_SPEED; // If space is pressed and not jumping, set a negative vertical velocity to jump up
        jumping = true;
    }
    x = sprite.getPosition().x;
    y = sprite.getPosition().y + vy;
    vy += GRAVITY;
    if (y > SCREEN_HEIGHT - GROUND_HEIGHT - DINO_HEIGHT)
    {
        y = SCREEN_HEIGHT - GROUND_HEIGHT - DINO_HEIGHT;
        vy = 0;          // Set vertical velocity to zero
        jumping = false; // Set jumping to false
    }
    sprite.setPosition(x, y);
}