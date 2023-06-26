#include "../headers/Engine.h"
#include <SFML/Graphics.hpp>
#include <random>
#include <fstream>

Engine::Engine() {
    resolution = Vector2f(900, 600);
    window.create(VideoMode(resolution.x, resolution.y), "Sneaky Snake", Style::Default);
    window.setFramerateLimit(FPS);

    maxLevels=0;
    checkLevelFiles();

    startTheGame();

    mainFont.loadFromFile("C:/Users/asus/CLionProjects/Snake/assets/fonts/slant_regular.ttf");

    setupText(&titleText,mainFont,"Sneaky Snake",28,Color::White);
    FloatRect titleTextBounds = titleText.getLocalBounds();
    titleText.setPosition(Vector2f(resolution.x/2 - titleTextBounds.width/2  ,-9));

    setupText(&currentLevelText, mainFont ,"level 1", 28, Color::White);
    currentLevelText.setPosition(Vector2f(15,-9));
    FloatRect currentLevelTextBounds = currentLevelText.getGlobalBounds();

    setupText(&applesEatenText,mainFont,"apples 0",28,Color::White);
    applesEatenText.setPosition(Vector2f(currentLevelTextBounds.left +currentLevelTextBounds.width + 20 , -9));

    setupText(&scoreText,mainFont, to_string(score),28,Color::White);
    FloatRect scoreTextBounds = scoreText.getGlobalBounds();
    scoreText.setPosition(Vector2f(resolution.x - scoreTextBounds.width - 15 ,-9));

}

void Engine::startTheGame() {
    score = 0;
    speed = 4;
    snakeDirection = Direction::RIGHT;

    timeSinceLastMove = Time::Zero;

    sectionsToAdd = 0;

    directionQueue.clear();
    //clearing the walls before next level
    wallSections.clear();

    applesEatenThisLevel=0;
    applesEatenTotal=0;

    currentLevel=1;
    loadLevel(&currentLevel);

    newSnake();
    moveApple();
    currentGameState = GameState::RUNNING;
    lastGameState = currentGameState;

    currentLevelText.setString("level " + to_string(currentLevel));
    applesEatenText.setString("apples " + to_string(applesEatenTotal));
    FloatRect currentLevelTextBounds = currentLevelText.getGlobalBounds();
    applesEatenText.setPosition(Vector2f(currentLevelTextBounds.left + currentLevelTextBounds.width +20, -9));
    setupText(&scoreText,mainFont, to_string(score),28,Color::White);
    FloatRect scoreTextBounds = scoreText.getGlobalBounds();
    scoreText.setPosition(Vector2f(resolution.x - scoreTextBounds.width - 15 ,-9));

}
//increment the level,load next level,reset snake
void Engine::beginNextLevel() {
    currentLevel +=1;
    wallSections.clear();
    directionQueue.clear();
    speed = 4 + currentLevel;
    snakeDirection = Direction::RIGHT;
    sectionsToAdd = 0;
    applesEatenThisLevel = 0;

    loadLevel(&currentLevel);
    newSnake();
    moveApple();
    currentLevelText.setString("level " + to_string(currentLevel));
    FloatRect currentLevelBounds = currentLevelText.getGlobalBounds();
    applesEatenText.setPosition(Vector2f(currentLevelBounds.left + currentLevelBounds.width + 20, -9));
}

//initial snake created at the start of each level
void Engine::newSnake() {
    //we clear the room first
    snake.clear();
    snake.emplace_back(Vector2f(100,100));
    snake.emplace_back(Vector2f(80,100));
    snake.emplace_back(Vector2f(60,100));
}

void Engine::addSnakeSection() {
    // adds the section at the same position as the last section of the snake
    /*
     * Vector2f newSectionPosition = snake[snake.size() - 1].getPosition();
     * snake.emplace_back(newSectionPosition);
     */
    Rect lastSectionRect = snake.back().getShape().getGlobalBounds();
    Vector2f newSectionPosition = Vector2f (lastSectionRect.left,lastSectionRect.top);
    snake.emplace_back(newSectionPosition);
}

void Engine::moveApple() {
    // Find a location to place the apple
    // Must not be inside the snake, or on a wall

    // Divide the field into sections the size of the apple - remove 2 to exclude the exterior walls
    Vector2f appleResolution = Vector2f(resolution.x / 20 -2, resolution.y / 20 - 2);
    Vector2f newAppleLocation;
    bool badLocation ;
    srand(time(nullptr));
    // Loop until we find a valid location
    do {
        badLocation = false;
        // Generate a random location
        newAppleLocation.x = (float)(1 + rand() / ((RAND_MAX + 1u) / (int)appleResolution.x)) * 20;
        newAppleLocation.y = (float)(1 + rand() / ((RAND_MAX + 1u) / (int)appleResolution.y)) * 20;

        // Check if it's in the snake
        for (auto &s : snake) {
            if(s.getShape().getGlobalBounds().intersects(
                    Rect<float>(newAppleLocation.x, newAppleLocation.y, 20, 20))) {
                badLocation = true;
                break;
            }
        }

        // check if it's in the walls
        for( auto & w : wallSections) {
            if (w.getShape().getGlobalBounds().intersects(
                    Rect<float>(newAppleLocation.x, newAppleLocation.y, 20, 20))) {
                badLocation = true;
                break;
            }
        }

    }while (badLocation);
    apple.setPosition(&newAppleLocation);
}

void Engine::togglePause() {
    if(currentGameState == GameState::RUNNING){
        lastGameState = currentGameState;
        currentGameState=GameState::PAUSED;
    }
    else if(currentGameState == GameState::PAUSED){
        currentGameState = lastGameState;
    }
}

void Engine::setupText(Text *textItem, const Font &font, const String &value, int size, Color color) {
    textItem->setFont(font);
    textItem->setString(value);
    textItem->setCharacterSize(size);
    textItem->setFillColor(color);
}


//check the levels manifest file and see if we can open each level file
//add level file names to "levels" vector and increment maxLevels
void Engine::checkLevelFiles() {
    //load levels manifest files
    ifstream levelsManifest ("C:/Users/asus/CLionProjects/Snake/assets/levels/levels.txt");
    ifstream testFile;
    for(string manifestLine; getline(levelsManifest,manifestLine);){
        //check that we can open level file
        testFile.open("C:/Users/asus/CLionProjects/Snake/assets/levels/" + manifestLine);
        //manifestLine hamoon masalan level1 o inas
        if(testFile.is_open()){
            levels.emplace_back("C:/Users/asus/CLionProjects/Snake/assets/levels/" + manifestLine);
            testFile.close();
            maxLevels++;
        }
    }
}

//load level file and check for 'x' to add wall sections
void Engine::loadLevel(const int *levelNumber) {
    string levelFile = levels[ *(levelNumber) - 1];
    ifstream level (levelFile);
    string line;
    if(level.is_open()){
        for (int y = 0; y < 30; y++){
            getline(level,line);
            for(int x = 0 ; x < 45 ;x++){
                if(line[x] == 'x'){
                    // emplace back is used to insert one new element to the end of a vector
                    wallSections.emplace_back(Wall(Vector2f(x * 20,y * 20),Vector2f(20 ,20 )));
                }
            }
        }
    }
    level.close();
}



void Engine::run() {
    Clock clock;

    // Main loop - Runs until the window is closed
    while (window.isOpen()) {
        Time dt = clock.restart();

        if(currentGameState == GameState::PAUSED || currentGameState == GameState::GAMEOVER){
            //if paused check for input to un-pause then continue to next loop
            input();

            //game over screen
            if (currentGameState ==GameState::GAMEOVER){
                draw();
            }

            //sleep to not max out cpu
            sleep(microseconds(2));
            continue;
        }


        timeSinceLastMove += dt;

        input();
        update();
        draw();
    }
}