class Obstacle;
int obstacleGap = 400;

// Define textures
sf::Texture obstacleTexture;
sf::Sprite obstacleSprite;

class Obstacle
{
private:
    int x, y;

public:
    Obstacle(int x)
    {
        // Load the texture file
        obstacleTexture.loadFromFile("assets/imgs/cactus.png");

        // Set the texture to the sprite
        obstacleSprite.setTexture(obstacleTexture);
        obstacleSprite.setColor(sf::Color::White);
        obstacleSprite.setScale(OBSTACLE_WIDTH / 100.0f, OBSTACLE_HEIGHT / 100.0f);

        this->x = x;                                                                   
        y = SCREEN_HEIGHT - GROUND_HEIGHT - OBSTACLE_HEIGHT;                           
        obstacleGap = ObstacleMinGap + rand() % (ObstacleMaxGap - ObstacleMinGap + 1); // Randomize the obstacle gap using the formula
    }

    void draw(sf::RenderWindow &window)
    {
        obstacleSprite.setPosition(x, y); // Set the position of the sprite
        window.draw(obstacleSprite);      // Draw the sprite on the window
    }

    void update()
    {
        x -= 5; 
    }

    int getX()
    {
        return x;
    }

    int getY()
    {
        return y;
    }
};