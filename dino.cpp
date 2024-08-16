// Include the necessary libraries
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

// Define some constants
#define SCREEN_WIDTH 800   // The width of the screen in pixels
#define SCREEN_HEIGHT 600  // The height of the screen in pixels
#define GROUND_HEIGHT 100  // The height of the ground in pixels
#define DINO_WIDTH 40      // The width of the dino
#define ObstacleMaxGap 450 // The maximum gap between object in pixels
#define DINO_HEIGHT 40     // The height of the dino in pixels
#define OBSTACLE_WIDTH 30  // The width of the obstacle in pixels
#define OBSTACLE_HEIGHT 30 // The height of the obstacle in pixels
int obstacleGap = 400;     // The gap between two obstacles in pixels
#define ObstacleMinGap 150 // The minimum gap between two obstacles in pixels
#define JUMP_SPEED 40      // The speed of the dino's jump in pixels per frame
#define GRAVITY 2          // The gravity of the dino in pixels per frame
int score = 0;
int highscore = 0;
int bonus = 0;

// Define some colors
sf::Color GROUND_COLOR = sf::Color(0xa23331ff); // The color of the ground
sf::Texture obstacleTexture;
sf::Sprite obstacleSprite;

// Forward declare a class for an obstacle
class Obstacle;

// Declare a class for the dino
class Dino
{
private:
    sf::Texture DinosuarTexture;
    sf::Sprite DinosuarSprite;
    int x, y;     // The position of the dino
    int vy;       // The vertical velocity of the dino
    bool jumping; // Whether the dino is jumping or not

public:
    Dino()
    {
        // Load the texture file
        DinosuarTexture.loadFromFile("assets/imgs/dino.png");

        // Set the texture to the sprite
        DinosuarSprite.setTexture(DinosuarTexture);
        DinosuarSprite.setColor(sf::Color::White);
        DinosuarSprite.setScale(DINO_WIDTH / 100.0f, DINO_HEIGHT / 100.0f);
        x = 100;                                         // Set the initial x position
        y = SCREEN_HEIGHT - GROUND_HEIGHT - DINO_HEIGHT; // Set the initial y position
        vy = 0;                                          // Set the initial vertical velocity
        jumping = false;                                 // Set the initial jumping state
    }

    // Draw the dino on a window
    void draw(sf::RenderWindow &window)
    {
        DinosuarSprite.setPosition(DinosuarSprite.getPosition().x, DinosuarSprite.getPosition().y);
        window.draw(DinosuarSprite);
    }

    /// Update the dino's state according to user input and physics
    void update()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !jumping)
        {
            vy = -JUMP_SPEED; // If space is pressed and not jumping, set a negative vertical velocity to jump up
            jumping = true;   // Set jumping to true
        }
        // Use the sprite's position instead of the y variable
        DinosuarSprite.setPosition(DinosuarSprite.getPosition().x, DinosuarSprite.getPosition().y + vy);
        vy += GRAVITY; // Update vertical velocity according to gravity
        if (DinosuarSprite.getPosition().y > SCREEN_HEIGHT - GROUND_HEIGHT - DINO_HEIGHT)
        {
            // Use the sprite's position instead of the y variable
            DinosuarSprite.setPosition(DinosuarSprite.getPosition().x, SCREEN_HEIGHT - GROUND_HEIGHT - DINO_HEIGHT); // If y position is below the ground, set it to the ground level
            vy = 0;                                                                                                  // Set vertical velocity to zero
            jumping = false;                                                                                         // Set jumping to false
        }
    }

    // Check if the dino collides with an obstacle
    bool collide(Obstacle &obstacle);
    // Forward declare this method as it depends on Obstacle class definition
};

// Declare a class for an obstacle
class Obstacle
{
private:
    int x, y; // The position of the obstacle

public:
    // Constructor with a given x position and a random y position on the ground
    Obstacle(int x)
    {
        // Load the texture file
        obstacleTexture.loadFromFile("assets/imgs/cactus.png");

        // Set the texture to the sprite
        obstacleSprite.setTexture(obstacleTexture);
        obstacleSprite.setColor(sf::Color::White);
        obstacleSprite.setScale(OBSTACLE_WIDTH / 100.0f, OBSTACLE_HEIGHT / 100.0f);

        this->x = x;                                                                   // Set the x position to the given value
        y = SCREEN_HEIGHT - GROUND_HEIGHT - OBSTACLE_HEIGHT;                           // Set the y position to the ground level
        obstacleGap = ObstacleMinGap + rand() % (ObstacleMaxGap - ObstacleMinGap + 1); // Randomize the obstacle gap using the formula
    }

    // Draw the obstacle on a window
    void draw(sf::RenderWindow &window)
    {
        obstacleSprite.setPosition(x, y); // Set the position of the sprite
        window.draw(obstacleSprite);      // Draw the sprite on the window
    }

    // Update the obstacle's state by moving it to the left
    void update()
    {
        x -= 5; // Move the x position to the left by 5 pixels per frame
    }

    // Get the x position of the obstacle
    int getX()
    {
        return x;
    }

    // Get the y position of the obstacle
    int getY()
    {
        return y;
    }
};

// Define the collide method for the dino class
bool Dino::collide(Obstacle &obstacle)
{
    return (x + DINO_WIDTH > obstacle.getX() && x < obstacle.getX() + OBSTACLE_WIDTH &&
            y + DINO_HEIGHT > obstacle.getY() && y < obstacle.getY() + OBSTACLE_HEIGHT);
    // Return true if there is an overlap between the dino and the obstacle, false otherwise
}

// Declare a class for the game
class Game
{
private:
    sf::RenderWindow window;         // The window of the game
    Dino dino;                       // The dino object
    std::vector<Obstacle> obstacles; // A vector of obstacle objects
    bool gameOver;                   // Whether the game is over or not

public:
    // Constructor
    Game()
    {
        window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Dino Game"); // Create the window with a title
        window.setFramerateLimit(60);                                           // Set the frame rate limit to 60 fps
        gameOver = false;                                                       // Set the game over state to false
        obstacles.push_back(Obstacle(SCREEN_WIDTH));
        // Add an initial obstacle at the right edge of the screen
        srand(time(NULL));
        // Initialize the random seed with the current time
    }

    // Run the game loop
    void run()
    {
        while (window.isOpen())
        {
            // While the window is open, repeat these steps:
            handleEvents(); // Handle user events such as closing the window or pressing a key
            update();       // Update the game state such as positions and collisions
            render();       // Render the game graphics such as shapes and colors
        }
    }

private:
    // Handle user events
    void handleEvents()
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // While there are events in the queue, process each one:
            if (event.type == sf::Event::Closed)
            {
                window.close();
                // If the event is closing the window, close it
            }
        }
    }

    // Update the game state
    void update()
    {
        // Update the score and highscore variables
        score += 1 + bonus; // add the bonus to the score
        if (gameOver)
        {
            if (score > highscore)
            {
                highscore = score;
            }
            score = 0;
        }

        else if (!gameOver)
        {
            dino.update();
            // Update the dino's state if the game is not over

            for (int i = 0; i < obstacles.size(); i++)
            {
                obstacles[i].update();
                // Update each obstacle's state

                if (dino.collide(obstacles[i]))
                {
                    gameOver = true;
                    break;
                    // If the dino collides with any obstacle, set the game over state to true and break out of the loop
                }
            }

            if (obstacles.back().getX() < SCREEN_WIDTH - obstacleGap)
            {
                obstacles.push_back(Obstacle(SCREEN_WIDTH));
                // If the last obstacle is far enough from the right edge of the screen, add a new obstacle at that edge
                obstacleGap = ObstacleMinGap + rand() % (ObstacleMaxGap - ObstacleMinGap + 1);
                // Randomize the obstacle gap for the next obstacle
            }

            if (obstacles.front().getX() < -OBSTACLE_WIDTH)
            {
                obstacles.erase(obstacles.begin());
                // If the first obstacle is out of the left edge of the screen, remove it from the vector
            }
        }
    }

    // Render the game graphics
    void render()
    {
        // Draw sky Image
        sf::Texture skyTexture;
        skyTexture.loadFromFile("assets/imgs/sky.png");
        sf::Sprite skySprite;
        skySprite.setTexture(skyTexture);
        window.draw(skySprite);

        sf::RectangleShape ground;
        ground.setSize(sf::Vector2f(SCREEN_WIDTH, GROUND_HEIGHT));
        ground.setFillColor(GROUND_COLOR);
        ground.setPosition(0, SCREEN_HEIGHT - GROUND_HEIGHT);
        window.draw(ground);
        // Draw a rectangle for the ground

        // Draw the dino
        dino.draw(window);

        for (int i = 0; i < obstacles.size(); i++)
        {
            obstacles[i].draw(window);
            // Draw each obstacle
        }

        // Create two text objects to display the score and the highscore
        sf::Font font;
        sf::Text scoreText, highscoreText;
        font.loadFromFile("assets/fonts/pixelated.ttf");

        // Set the font for both texts
        scoreText.setFont(font);
        highscoreText.setFont(font);

        // Set the character size for both texts
        scoreText.setCharacterSize(20);
        highscoreText.setCharacterSize(20);

        // Set the color for both texts
        scoreText.setFillColor(sf::Color::White);
        highscoreText.setFillColor(sf::Color::White);

        // Set the string for both texts using std::to_string to convert int to string
        scoreText.setString("score: " + std::to_string(score));
        highscoreText.setString("highscore: " + std::to_string(highscore));

        // Set the position for both texts on the left corner with some margin
        scoreText.setPosition(590, 10);
        highscoreText.setPosition(590, 40);

        // Draw both texts on the window
        window.draw(scoreText);
        window.draw(highscoreText);

        if (gameOver)
        {
            sf::Font font;
            font.loadFromFile("pixelated.ttf");

            sf::Text text;
            text.setFont(font);
            text.setString("Game Over");
            text.setCharacterSize(50);
            text.setFillColor(sf::Color::Red);

            text.setPosition(SCREEN_WIDTH / 2 - text.getLocalBounds().width / 2, SCREEN_HEIGHT / 2 - text.getLocalBounds().height / 2);
            // Set the position of the text at the center of the screen

            window.draw(text);
            // Draw the text on the window
        }

        window.display();
        // Display the window
    }
};

// The main function
int main()
{
    Game game;  // Create a game object
    game.run(); // Run the game loop
    return 0;   // Return 0 when the program ends
}
