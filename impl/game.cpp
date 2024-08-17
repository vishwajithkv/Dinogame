#include "headers/game.hpp"
#include "headers/dino.hpp"
#include "headers/obstacle.hpp"
#include "SFML/Graphics.hpp"
#include "headers/constants.hpp"
#include <cstdlib>
#include <ctime>

using namespace sf;

inline int getObstacleGap()
{
    return OBSTACLE_MIN_GAP + rand() % (OBSTACLE_MAX_GAP - OBSTACLE_MIN_GAP + 1);
}

Game::Game()
{
    window.create(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Dino Game");
    window.setFramerateLimit(FRAME_RATE);

    highScore = 0;
    reset();
}

void Game::deleteObstacles()
{
    for (auto obstacle : obstacles)
    {
        delete obstacle;
    }
}

void Game::reset()
{
    srand(time(NULL));
    obstacleGap = getObstacleGap();
    obstacles.push_back(new Obstacle(SCREEN_WIDTH));

    gameOver = false;
    score = 0;
    bonus = 0;
}

void Game::run()
{
    while (window.isOpen())
    {
        handleEvents();
        update();
        render();
    }
}

void Game::handleEvents()
{
    Event event;
    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed)
        {
            deleteObstacles();
            window.close();
        }
    }
}

void Game::update()
{
    score += 1 + bonus;
    if (gameOver)
    {
        if (score > highScore)
        {
            highScore = score;
        }
        score = 0;
        return;
    }

    if (obstacles.back()->getX() < SCREEN_WIDTH - obstacleGap)
    {
        obstacles.push_back(new Obstacle(SCREEN_WIDTH));
        obstacleGap = getObstacleGap();
    }
    if (obstacles.front()->getX() < -OBSTACLE_WIDTH)
    {
        delete obstacles[0];
        obstacles.erase(obstacles.begin());
    }

    dino.update();
    for (auto obstacle : obstacles)
    {
        obstacle->update();
        if (isColliding(dino, *obstacle))
        {
            gameOver = true;
            break;
        }
    }
}

void Game::render()
{
    sf::Texture skyTexture;
    skyTexture.loadFromFile("assets/imgs/sky.png");
    sf::Sprite skySprite;
    skySprite.setTexture(skyTexture);
    window.draw(skySprite);

    sf::RectangleShape ground;
    ground.setSize(sf::Vector2f(SCREEN_WIDTH, GROUND_HEIGHT));
    ground.setFillColor(Color(GROUND_COLOR));
    ground.setPosition(0, SCREEN_HEIGHT - GROUND_HEIGHT);

    window.draw(ground);
    window.draw(dino);
    for (auto obstacle : obstacles)
    {
        window.draw(*obstacle);
    }

    sf::Font font;
    sf::Text scoreText, highscoreText;
    font.loadFromFile("assets/fonts/pixelated.ttf");

    scoreText.setFont(font);
    highscoreText.setFont(font);

    scoreText.setCharacterSize(20);
    highscoreText.setCharacterSize(20);

    scoreText.setFillColor(Color::White);
    highscoreText.setFillColor(Color::White);

    // string for both texts using std::to_string to convert int to string
    scoreText.setString("score: " + std::to_string(score));
    highscoreText.setString("highscore: " + std::to_string(highScore));

    // position for both texts on the left corner with some margin
    scoreText.setPosition(590, 10);
    highscoreText.setPosition(590, 40);

    window.draw(scoreText);
    window.draw(highscoreText);

    if (gameOver)
    {
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

bool isColliding(Dino &dino, Obstacle &obstacle)
{
    // Get the bounding boxes of both objects
    int dinoLeft = dino.getX();
    int dinoRight = dinoLeft + DINO_WIDTH;
    int dinoTop = dino.getY();
    int dinoBottom = dinoTop + DINO_HEIGHT;

    int obstacleLeft = obstacle.getX();
    int obstacleRight = obstacleLeft + OBSTACLE_WIDTH;
    int obstacleTop = obstacle.getY();
    int obstacleBottom = obstacleTop + OBSTACLE_HEIGHT;

    return (dinoRight >= obstacleLeft) && (dinoLeft <= obstacleRight) && (dinoBottom >= obstacleTop) && (dinoTop <= obstacleBottom);
}