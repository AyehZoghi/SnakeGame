#include "../headers/Engine.h"
#include "../headers/MainMenu.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;
using namespace std;
int main() {
    //Make a main window
    RenderWindow window(VideoMode(900, 600), "Sneaky Snake", Style::Default);
    MainMenu mainMenu(window.getSize().x, window.getSize().y);

    //set music
    Music music;
    if(!music.openFromFile("C:/Users/asus/CLionProjects/Snake/assets/music/GameTheme.ogg")){
        cout<<"cant open";
    }
    music.setVolume(60);


    //set background
    RectangleShape background;
    background.setSize(Vector2f(900,600));
    Texture MainTexture;
    MainTexture.loadFromFile("C:/Users/asus/CLionProjects/Snake/assets/images/Snake.jfif");
    background.setTexture(&MainTexture);

    //set About
    RectangleShape AboutBackground;
    AboutBackground.setSize(Vector2f(900, 600));
    Texture AboutTexture;
    AboutTexture.loadFromFile("C:/Users/asus/CLionProjects/Snake/assets/images/About.png");
    AboutBackground.setTexture(&AboutTexture);


    while(window.isOpen())
    {
        Event event{};
        while(window.pollEvent(event))
        {
            if(event.type == Event::Closed)
            {
                window.close();
            }
            if(event.type == Event::KeyReleased) {
                if (event.key.code == Keyboard::Up) {
                    mainMenu.MoveUp();
                }
                if (event.key.code == Keyboard::Down) {
                    mainMenu.MoveDown();
                }
                if(event.key.code == Keyboard::Return ){

                    int x = mainMenu.MainMenuPressed();
                    if(x==0)
                    {
                        music.play();
                        music.setLoop(true);
                        Engine engine;
                        engine.run();
                        music.stop();
                    }
                    if(x==1) {
                        RenderWindow About(VideoMode(900, 600), "How to Play", Style::Default);
                        while (About.isOpen()) {
                            Event aevent{};
                            while (About.pollEvent(aevent)) {
                                if (aevent.type == Event::Closed || aevent.key.code == Keyboard::Escape ) {
                                    About.close();
                                }
                            }
                            About.clear();
                            About.draw( AboutBackground);
                            About.display();
                        }
                    }
                    if (x==2)
                        window.close();
                }
            }
        }
        window.clear();
        window.draw(background);
        mainMenu.draw(&window);
        window.display();
    }

}