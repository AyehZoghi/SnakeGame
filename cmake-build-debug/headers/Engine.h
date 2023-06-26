#ifndef SNAKE_ENGINE_H
#define SNAKE_ENGINE_H
#pragma once
#include "../headers/SnakeSection.h"
#include "../headers/Apple.h"
#include "../headers/Wall.h"
#include<SFML/Graphics.hpp>
#include<SFML/Graphics/RectangleShape.hpp>
#include<vector>
#include<deque>
#include<istream>

using namespace sf;
using namespace std;

class Engine {
private:
    //window
    Vector2f resolution;
    RenderWindow window;
    const unsigned int FPS = 60;

    vector<SnakeSection> snake;
    int snakeDirection{};
    //queue for direction key presses
    deque<int> directionQueue;

    int speed{};
    //sections to add to the snake
    int sectionsToAdd{};

    int applesEatenThisLevel{};
    int applesEatenTotal{};
    const unsigned int applesForNextLevel = 5;
    unsigned long long int score{};

    Apple apple;

    vector<Wall>wallSections;
    int currentLevel{};
    int maxLevels;
    vector<String>levels;


    Text titleText;
    Text applesEatenText;
    Text currentLevelText;
    Text scoreText;
    Font mainFont;

    //to move step by step instead of constantly moving
    Time timeSinceLastMove;
    int currentGameState{};
    //start the game in the last state it was after pausing
    int lastGameState{};

public:

    enum Direction {UP, RIGHT, DOWN, LEFT};
    enum GameState {RUNNING,PAUSED,GAMEOVER};
    Engine();


    void input();
    void addDirection(int newDirection);
    void update();

    void draw();

    static void setupText(Text *textItem, const Font &font, const String &value, int size, Color color);

    void newSnake();
    void addSnakeSection();

    void beginNextLevel();
    void startTheGame();

    void moveApple();
    void checkLevelFiles();
    void loadLevel(const int *levelNumber);
    void togglePause();

    //the main loop will be in the run function
    void run();

};


#endif //SNAKE_ENGINE_H
