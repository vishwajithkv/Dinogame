#ifndef CONSTANTS_H
#define CONSTANTS_H

constexpr int SCREEN_WIDTH = 800;  // The width of the screen in pixels
constexpr int SCREEN_HEIGHT = 600; // The height of the screen in pixels
constexpr int GROUND_HEIGHT = 100; // The height of the ground in pixels

constexpr int OBSTACLE_MAX_GAP = 450; // The maximum gap between object in pixels
constexpr int OBSTACLE_MIN_GAP = 150; // The minimum gap between two obstacles in pixels
constexpr int OBSTACLE_WIDTH = 30;    // The width of the obstacle in pixels
constexpr int OBSTACLE_HEIGHT = 30;   // The height of the obstacle in pixels

constexpr int DINO_WIDTH = 40;  // The width of the dino
constexpr int DINO_HEIGHT = 40; // The height of the dino in pixels
constexpr int JUMP_SPEED = 50;  // The speed of the dino's jump in pixels per frame

constexpr int GRAVITY = 3; // The gravity of the dino in pixels per frame
constexpr int OBSTACLE_SPEED = 10;

constexpr int FRAME_RATE = 90;
constexpr double GROUND_COLOR = 0xa23331ff;

#endif