#include "../headers/Engine.h"

void Engine::input() {
    Event event{};

    while (window.pollEvent(event)) {
        //closes window
        if (event.type == Event::Closed) {
            window.close();
        }

        //keyboard input check
        if (event.type == Event::KeyPressed) {
            //Quit (biron ba escape)
            if (event.key.code == Keyboard::Escape) {
                window.close();
            }


            //pause
            if (event.key.code == Keyboard::Space)
                togglePause();

            //new game
            if(currentGameState == GameState::GAMEOVER){
                if(event.key.code == Keyboard::Enter){
                    startTheGame();
                }
            }

            //cheat codes
            if(event.key.code == Keyboard::M){
                moveApple();
            }
            if(event.key.code == Keyboard::B){
                if(currentLevel<3){
                beginNextLevel();}
            }
            if(event.key.code == Keyboard::Add){
                sectionsToAdd +=4;
            }

            //direction
            if (event.key.code == Keyboard::Up) {
                addDirection(Direction::UP);
            } else if (event.key.code == Keyboard::Down) {
                addDirection(Direction::DOWN);
            } else if (event.key.code == Keyboard::Left) {
                addDirection(Direction::LEFT);
            } else if (event.key.code == Keyboard::Right) {
                addDirection(Direction::RIGHT);
            }
        }
    }
}
void Engine::addDirection(int newDirection) {
    if(directionQueue.empty()){
        directionQueue.emplace_back(newDirection);
    }
    else{
        //age masalan rast miraft baz rast o nazani
        if(directionQueue.back() != newDirection){
            directionQueue.emplace_back(newDirection);
        }
    }
}