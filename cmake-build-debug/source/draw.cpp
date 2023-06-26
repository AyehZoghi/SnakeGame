#include "../headers/Engine.h"

void Engine::draw() {
    window.clear(Color::Black);
    //image to the game
    RectangleShape PBackGround;
    PBackGround.setSize(Vector2f(900,600));
    Texture back_Texture;
    back_Texture.loadFromFile("C:/Users/asus/CLionProjects/Snake/assets/images/background.jfif");
    PBackGround.setTexture(&back_Texture);
    window.draw(PBackGround);

    //draw walls
    for (auto & w :wallSections){
        window.draw(w.getShape());
    }

    //draw apple
    window.draw(apple.getSprite());

    //draw snake sections
    for (auto & s :snake){
        window.draw(s.getShape());
    }

    //draw text
    window.draw(titleText);
    window.draw(currentLevelText);
    window.draw(applesEatenText);
    window.draw(scoreText);

    //draw game-over
    if(currentGameState == GameState::GAMEOVER) {
        RectangleShape GameOverBackGround;
        GameOverBackGround.setSize(Vector2f(900,600));
        Texture GameOver_Texture;
        GameOver_Texture.loadFromFile("C:/Users/asus/CLionProjects/Snake/assets/images/GAMEOVER.png");
        GameOverBackGround.setTexture(&GameOver_Texture);
        window.draw(GameOverBackGround);
    }

    window.display();
}
