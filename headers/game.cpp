int score = 0;             
int highscore = 0;
int bonus = 0;

// Ground color
sf::Color GROUND_COLOR = sf::Color(0xa23331ff); 

class Game
{
private:
    sf::RenderWindow window;         // The window of the game
    Dino dino;                       // The dino object
    std::vector<Obstacle> obstacles; // A vector of obstacle objects
    bool gameOver;                   // Whether the game is over or not

public:
    Game()
    {
        window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Dino Game");
        window.setFramerateLimit(60);                                           // Set the frame rate limit to 60 fps
        gameOver = false;                                                       
        obstacles.push_back(Obstacle(SCREEN_WIDTH));
        srand(time(NULL));
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
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
    }

    // Update the game state
    void update()
    {
        score += 1 + bonus;
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
                }
            }

            if (obstacles.back().getX() < SCREEN_WIDTH - obstacleGap)
            {
                obstacles.push_back(Obstacle(SCREEN_WIDTH));
                obstacleGap = ObstacleMinGap + rand() % (ObstacleMaxGap - ObstacleMinGap + 1);
            }

            if (obstacles.front().getX() < -OBSTACLE_WIDTH)
            {
                obstacles.erase(obstacles.begin());
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

        // Draw a rectangle for the ground
        sf::RectangleShape ground;
        ground.setSize(sf::Vector2f(SCREEN_WIDTH, GROUND_HEIGHT));
        ground.setFillColor(GROUND_COLOR);
        ground.setPosition(0, SCREEN_HEIGHT - GROUND_HEIGHT);
        window.draw(ground);
        
        // Draw the dino
        dino.draw(window);

        for (int i = 0; i < obstacles.size(); i++)
        {
            // Draw each obstacle
            obstacles[i].draw(window);
        }

        //  display the score and the highscore
        sf::Font font;
        sf::Text scoreText, highscoreText;
        font.loadFromFile("assets/fonts/pixelated.ttf");

        // font for both texts
        scoreText.setFont(font);
        highscoreText.setFont(font);

        // character size for both texts
        scoreText.setCharacterSize(20);
        highscoreText.setCharacterSize(20);

        // color for both texts
        scoreText.setFillColor(sf::Color::White);
        highscoreText.setFillColor(sf::Color::White);

        // string for both texts using std::to_string to convert int to string
        scoreText.setString("score: " + std::to_string(score));
        highscoreText.setString("highscore: " + std::to_string(highscore));

        //position for both texts on the left corner with some margin
        scoreText.setPosition(590, 10);
        highscoreText.setPosition(590, 40);

        // Draw both texts
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

            window.draw(text);
        }

        window.display();
    }
};