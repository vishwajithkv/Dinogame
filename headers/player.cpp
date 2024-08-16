#include "constants.h"
#include "obstacle.cpp"

class Dino
{
private:
    sf::Texture DinosuarTexture;
    sf::Sprite DinosuarSprite;
    int x, y;     
    int vy;      
    bool jumping; 

public:
    Dino()
    {
        // Load the texture file
        DinosuarTexture.loadFromFile("assets/imgs/dino.png");

        // Set the texture to the sprite
        DinosuarSprite.setTexture(DinosuarTexture);
        DinosuarSprite.setColor(sf::Color::White);
        DinosuarSprite.setScale(DINO_WIDTH / 100.0f, DINO_HEIGHT / 100.0f);
        x = 100;                                         
        y = SCREEN_HEIGHT - GROUND_HEIGHT - DINO_HEIGHT; 
        vy = 0;                                          
        jumping = false;                               
    }

    // Draw the dino
    void draw(sf::RenderWindow &window)
    {
        DinosuarSprite.setPosition(DinosuarSprite.getPosition().x, DinosuarSprite.getPosition().y);
        window.draw(DinosuarSprite);
    }

    // Update the dino's state according to user input
    void update()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !jumping)
        {
            vy = -JUMP_SPEED; // If space is pressed and not jumping, set a negative vertical velocity to jump up
            jumping = true;  
        }
        DinosuarSprite.setPosition(DinosuarSprite.getPosition().x, DinosuarSprite.getPosition().y + vy);
        vy += GRAVITY; 
        if (DinosuarSprite.getPosition().y > SCREEN_HEIGHT - GROUND_HEIGHT - DINO_HEIGHT)
        {
            DinosuarSprite.setPosition(DinosuarSprite.getPosition().x, SCREEN_HEIGHT - GROUND_HEIGHT - DINO_HEIGHT); // If y position is below the ground, set it to the ground level
            vy = 0;                                                                                                  // Set vertical velocity to zero
            jumping = false;                                                                                         // Set jumping to false
        }
    }
    
    bool collide(Obstacle &obstacle);
};