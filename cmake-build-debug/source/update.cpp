#include <string>
#include "../headers/Engine.h"

void Engine::update() {
    //position snake update she
    if(timeSinceLastMove.asSeconds() >= seconds(1.f / float(speed)).asSeconds()){
        /*
         *   Vector2f thisSectionPosition = snake[0].getPosition();
         *   Vector2f lastSectionPosition = thisSectionPosition;
         *    alani mire ja ghabli baed khode alani mishe ghabli (vase baedi)
         */
        Rect lastSectionRect = snake.front().getShape().getGlobalBounds();
        Vector2f thisSectionPosition = Vector2f (lastSectionRect.left,lastSectionRect.top);
        Vector2f lastSectionPosition = thisSectionPosition;

    // does the snake need to change position?
    if (!directionQueue.empty()){
        //yoho chap baede rast nazane bere to ham ya bala paiin
        switch(snakeDirection){
            case Direction::UP:
                if(directionQueue.front() != Direction::DOWN){
                    snakeDirection = directionQueue.front();
                }
                break;
            case Direction::DOWN:
                if(directionQueue.front() != Direction::UP){
                    snakeDirection = directionQueue.front();
                }
                break;
            case Direction::RIGHT:
                if(directionQueue.front() != Direction::LEFT){
                    snakeDirection = directionQueue.front();
                }
                break;
            case Direction::LEFT:
                if(directionQueue.front() != Direction::RIGHT){
                    snakeDirection = directionQueue.front();
                }
                break;
        }
        directionQueue.pop_front();
    }

    //update score
    score += snake.size() + applesEatenTotal;
    scoreText.setString(to_string((score)));
        FloatRect scoreTextBounds = scoreText.getGlobalBounds();
        scoreText.setPosition(Vector2f(resolution.x - scoreTextBounds.width - 15 ,-9));

    //do we need to grow the snake?
    if(sectionsToAdd){
        addSnakeSection();
        sectionsToAdd--;
    }

    //update the snakes head position
    switch(snakeDirection){
        case Direction::RIGHT:
            snake[0].setPosition(Vector2f(thisSectionPosition.x+20,thisSectionPosition.y));
            break;
        case Direction::LEFT:
            snake[0].setPosition(Vector2f(thisSectionPosition.x-20,thisSectionPosition.y));
            break;
        case Direction::UP:
            snake[0].setPosition(Vector2f(thisSectionPosition.x,thisSectionPosition.y-20));
            break;
        case Direction::DOWN:
            snake[0].setPosition(Vector2f(thisSectionPosition.x,thisSectionPosition.y+20));
            break;
    }

    //update the snakes tail position
    for( int s=1 ;s<snake.size();s++){
        /*
         *  thisSectionPosition = snake[s].getPosition();
         *  snake[s].setPosition(lastSectionPosition);
         *  lastSectionPosition = thisSectionPosition;
         *  alani mire ja ghabli baed khode alani mishe ghabli (vase baedi)
         */
        lastSectionRect = snake[s].getShape().getGlobalBounds();
        thisSectionPosition = Vector2f (lastSectionRect.left,lastSectionRect.top);
        snake[s].setPosition(lastSectionPosition);
        lastSectionPosition = thisSectionPosition;
    }

    //collision detection - apple
    if(snake[0].getShape().getGlobalBounds().intersects(apple.getSprite().getGlobalBounds())){
        // when hits apple -> add more sections to snake,increase speed,move apple
        applesEatenThisLevel+=1;
        applesEatenTotal+=1;
        applesEatenText.setString("apples " + to_string(applesEatenTotal));
        FloatRect currentLevelTextBounds = currentLevelText.getGlobalBounds();
        applesEatenText.setPosition(Vector2f(currentLevelTextBounds.left + currentLevelTextBounds.width +20, -9));

        bool beggingNextLevel = false;
        if(applesEatenThisLevel >= applesForNextLevel) {
            //go next level if more
            if (currentLevel < maxLevels) {
                beggingNextLevel = true;
                beginNextLevel();
            }
        }
            if(!beggingNextLevel){
                sectionsToAdd += 4;
                speed++;
                moveApple();
            }
        }
    //Snake body collision detection
    for(int s=1 ; s<snake.size();s++) {
        if (snake[0].getShape().getGlobalBounds().intersects(snake[s].getShape().getGlobalBounds())) {
            //GAME OVER
            currentGameState = GameState::GAMEOVER;
        }
    }
    //Wall collision detection
    for( auto & w : wallSections){
        if (snake[0].getShape().getGlobalBounds().intersects(w.getShape().getGlobalBounds())){
            //GAME OVER
            currentGameState = GameState::GAMEOVER;
        }
    }

    //reset last move timer
timeSinceLastMove = Time::Zero;

    }//end of snake position update
}

